
% problem 2
% b) find the steady state distrbution
P = [ 7/8 1/8 0; 7/80 4/5 9/80; 7/800 127/800 333/400];
A = [ P'-eye(3); 1 1 1];
b = [0; 0; 0; 1];
% answer
pi = A\b;

% problem 5
% c)
res = 1 - poisscdf(39, 30)

% problem 6
% Simulation D/Gam/1 queuing system
alpha = 4;
lambda = 10/3; % param's for Gamma distribution for service times
t = 15; % fixed interarrival time
N = input('size of the Monte Carlo study='); % Number of simulations
arr_times = 0:t:(N-1) * t; % arrivals 0,t,2t,...
service_start = zeros(1, N);
serv_start = zeros(1, N); % times when service starts
serv_finish = zeros(1, N); % times when service finishes
A = 0; % time when doctor becomes available

for j = 1 : N
    serv_start(j) = max(A, arr_times(j));
    service(j) = -lambda * sum(log(rand(1,alpha))); % Sim. Gamma(alpha,gamma)
    % as sum of alpha Exp(1/lambda) var's
    serv_finish(j) = serv_start(j) + service(j);
    A = serv_finish(j);
end

fprintf('a) expected response time E(R) is %3.5f\n', mean(serv_finish - arr_times));
fprintf('b) expected waiting time E(W) is %3.5f\n', mean(serv_start - arr_times));
fprintf('c) P(W>0) is %3.5f\n', mean(serv_start > arr_times));
