
import repository.Repository;
import ui.DoctorUI;
import controller.DoctorController;

public class App {

	public static void main(String[] args) {
		String patients = "FilePatients.txt";
		String consultations = "FileConsultations.txt";
		Repository repo = new Repository(patients, consultations);
		DoctorController ctrl = new DoctorController(repo);
		
		DoctorUI console = new DoctorUI(ctrl);
		console.Run();
	}
}
