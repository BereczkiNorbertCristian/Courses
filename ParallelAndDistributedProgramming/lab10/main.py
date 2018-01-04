
from multiprocessing import Pool, Process, Manager
import os,os.path
import time
import queue

# (2 -> Prepare, variable_id, new_value, OPERATION_ID, pseudo_lamport_timestamp)
# (3 -> Commit, variable_id,new_value, OPERATION_ID, pseudo_lamport_timestamp)

TIME_TO_WAIT = 2  # seconds
OPERATION_TYPE = 0
VARIABLE_ID = 1
NEW_VALUE = 2
OPERATION_ID = 3
PSEUDO_LAMPORT_TIMESTAMP = 4

# Operation types
TO_DO_OPERATION = 1
PREPARE_OPERATION = 2
OK_OPERATION = 3
COMMIT_OPERATION = 4
SLEEP_OPERATION = 5


def log(filename, to_write):
	file_operation = "a"
	if not os.path.exists(filename):
		file_operation = "w"
	with open(filename, file_operation) as f:
		f.write(to_write + "\n")


def pretify_operation_type(operation_type):
	global PREPARE_OPERATION
	global COMMIT_OPERATION
	global OK_OPERATION
	global TO_DO_OPERATION
	global SLEEP_OPERATION
	if operation_type == PREPARE_OPERATION:
		return "Prepare"
	elif operation_type == COMMIT_OPERATION:
		return "Commit"
	elif operation_type == OK_OPERATION:
		return "Ok"
	elif operation_type == TO_DO_OPERATION:
		return "TODO"
	elif operation_type == SLEEP_OPERATION:
		return "Sleep"
	return "None"


def dict_from_tuple(tpl):
	global OPERATION_TYPE
	global VARIABLE_ID
	global NEW_VALUE
	global OPERATION_ID
	global PSEUDO_LAMPORT_TIMESTAMP
	return {
		'OPERATION': pretify_operation_type(tpl[OPERATION_TYPE]),
		'VARIABLE_ID': tpl[VARIABLE_ID],
		'NEW_VALUE': tpl[NEW_VALUE],
		'OPERATION_ID': tpl[OPERATION_ID],
		'LAMPORT_TIMESTAMP': tpl[PSEUDO_LAMPORT_TIMESTAMP]
	}


def format_tuple(tpl):
	result_string = '''({OPERATION}, var_idx: {VARIABLE_ID}, new_value: {NEW_VALUE}, operation_id: {OPERATION_ID}, Lamport_Timestamp: {LAMPORT_TIMESTAMP})'''
	dict = dict_from_tuple(tpl)
	return result_string.format(**dict)


def child(master_queue, my_queue, variables, operations):

	global TIME_TO_WAIT
	global OPERATION_TYPE
	global VARIABLE_ID
	global NEW_VALUE
	global OPERATION_ID
	global PREPARE_OPERATION
	global COMMIT_OPERATION
	global OK_OPERATION
	global PSEUDO_LAMPORT_TIMESTAMP
	global TO_DO_OPERATION

	log_filename = "logs/" + str(os.getpid()) + ".log"
	my_operations_idx = 0
	pseudo_lamport_timestamp = 0
	once = False

	while True:
		try:
			current = my_queue.get(block=True, timeout=TIME_TO_WAIT)
		except queue.Empty:
			current = None

		if current != None:
			pseudo_lamport_timestamp = max(
				pseudo_lamport_timestamp + 1, current[PSEUDO_LAMPORT_TIMESTAMP] + 1)
			to_log = (current[OPERATION_TYPE], current[VARIABLE_ID], current[
				NEW_VALUE], current[OPERATION_ID], pseudo_lamport_timestamp)
			log(log_filename, format_tuple(to_log))

			if current[OPERATION_TYPE] == PREPARE_OPERATION:
				pseudo_lamport_timestamp += 1
				to_put = (OK_OPERATION, current[VARIABLE_ID], current[
					NEW_VALUE], current[OPERATION_ID], pseudo_lamport_timestamp)
				log(log_filename, format_tuple(to_put))
				master_queue.put(to_put)

			elif current[OPERATION_TYPE] == COMMIT_OPERATION:
				pseudo_lamport_timestamp += 1
				to_log = (COMMIT_OPERATION, current[VARIABLE_ID], current[
					NEW_VALUE], current[OPERATION_ID], pseudo_lamport_timestamp)
				log(log_filename, format_tuple(to_log))
				variables[current[VARIABLE_ID]] = current[NEW_VALUE]

		if once == False and my_operations_idx == len(operations):
			print("Finished " + str(os.getpid()))
			once = True
		if my_operations_idx < len(operations):
			pseudo_lamport_timestamp += 1

			to_do_operation = operations[my_operations_idx]
			to_put = (TO_DO_OPERATION, to_do_operation[VARIABLE_ID], to_do_operation[
			          NEW_VALUE], -1, pseudo_lamport_timestamp)
			log(log_filename, format_tuple(to_put))
			master_queue.put(to_put)

			my_operations_idx += 1


def master(master_queue, child_queues, variables):
	global TIME_TO_WAIT
	global OPERATION_TYPE
	global VARIABLE_ID
	global NEW_VALUE
	global OPERATION_ID
	global PREPARE_OPERATION
	global COMMIT_OPERATION
	global OK_OPERATION
	global PSEUDO_LAMPORT_TIMESTAMP
	global TO_DO_OPERATION
	global SLEEP_OPERATION

	log_filename = "logs/master.log"
	pseudo_lamport_timestamp = 0
	in_progress_operations_dict = {}

	while True:
		try:
			current = master_queue.get(block=True, timeout=TIME_TO_WAIT)
		except queue.Empty:
			current = None

		if current != None:
			variable_id = current[VARIABLE_ID]
			new_value = current[NEW_VALUE]
			if current[OPERATION_TYPE] == TO_DO_OPERATION:
				if variable_id in in_progress_operations_dict.keys():
					master_queue.put((SLEEP_OPERATION, -1, -1, -1, -1))
					master_queue.put(current)
				else:
					for q_idx in range(0, len(child_queues)):
						pseudo_lamport_timestamp = max(
	    				    pseudo_lamport_timestamp + 1, current[PSEUDO_LAMPORT_TIMESTAMP] + 1)
						to_put = (PREPARE_OPERATION, variable_id, new_value,
	    				          current[VARIABLE_ID], pseudo_lamport_timestamp)
						child_queues[q_idx].put(to_put)
					in_progress_operations_dict[variable_id] = 0

			elif current[OPERATION_TYPE] == OK_OPERATION:
				in_progress_operations_dict[variable_id] += 1
				pseudo_lamport_timestamp = max(
	    		    pseudo_lamport_timestamp + 1, current[PSEUDO_LAMPORT_TIMESTAMP] + 1)
				to_log = (OK_OPERATION, variable_id, new_value, current[
	    		          OPERATION_ID], pseudo_lamport_timestamp)
				log(log_filename, format_tuple(to_log))

				if in_progress_operations_dict[variable_id] == len(child_queues):
					for q_idx in range(0, len(child_queues)):
						pseudo_lamport_timestamp = max(
						    pseudo_lamport_timestamp + 1, current[PSEUDO_LAMPORT_TIMESTAMP] + 1)
						to_put = (COMMIT_OPERATION, variable_id, new_value,
						          current[OPERATION_ID], pseudo_lamport_timestamp)
						log(log_filename, format_tuple(to_put))
						child_queues[q_idx].put(to_put)
					in_progress_operations_dict.pop(variable_id,None)


			elif current[OPERATION_TYPE] == SLEEP_OPERATION:
				log(log_filename,format_tuple(current))
				time.sleep(4)





def get_children_queues(no_ch, manager):
    ret = []
    for i in range(0, no_ch):
	    ret.append(manager.Queue())
    return ret


# (OPERATION TYPE,VARIABLE NUMBER, NEW VALUE)
def get_operations():
    return [
        [(1, 1, 3, -1, -1), (1, 2, 2, -1, -1), (1, 4, 12, -1, -1)],
        [(1, 2, 3, -1, -1), (1, 3, 4, -1, -1)],
        [(1, 3, 9, -1, -1), (1, 1, 1, -1, -1)]
    ]

if __name__ == '__main__':

    CHILDREN_NO = 2
    variables = [0] * 5
    operations = get_operations()

    manager = Manager()
    master_queue = manager.Queue()
    child_queues = get_children_queues(CHILDREN_NO, manager)

    master_process = Process(target=master, args=(master_queue, child_queues, variables,))
    processes = []
    for i in range(0, CHILDREN_NO):
        processes.append(Process(target=child, args=(
            master_queue, child_queues[i], variables, operations[i],)))

    master_process.start()
    for i in range(0, CHILDREN_NO):
    	processes[i].start()

    time.sleep(30000)
