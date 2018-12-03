% Counting processes

% First problem

% b)

P_X_60_eq_0 = binopdf(0,60,0.1);

% c)
P_X_1200_gt_100 = 1 - binopdf(100, 1200, 0.1);


% Second problem

% a)
P_no_offer = poisscdf(2, 10);

% b)
P_1_over_3 = 1 - expcdf(1/3, 1/5);

% c)

% Problem 4
% Simulate a Binomial counting process

Nb = input('size of sample path=');
p = input('prob. of arrival(success)=');
X = zeros(1, Nb);
X(1) = (rand < p);
for t = 2:Nb
    X(t) =  X(t-1) + (rand < p); % count nr. of successes
end
X

% Problem 5
% illustration
Del = input('frame size (in seconds)=');
axis([0 Nb 0 max(X)]); % allocate the box for the graph
hold on;
title('Binomial Counting Process')
xlabel('time')
ylabel('nr. of arrivals');
for t = 1:Nb
    plot(t, X(t), '*', 'MarkerSize', 8);
%    pause(Del)
end
hold off;

% Simulate a  Poisson Counting process.
% [0, Tmax] segment

clf();
lambda = input('arrival rate='); % 5
Tmax = input('Tmax='); % 30
arr_time = - (1/lambda) * log(rand); % array of arrival times Exp(lambda) distributed
last_arrival = arr_time;
while last_arrival <= Tmax
    last_arrival = last_arrival - (1 / lambda) * log(rand);
    arr_time = [arr_time, last_arrival];
end
arr_time = arr_time(1:end-1); % last last_arrival should not be included

t = 0:0.01:Tmax;
Nsteps = length(t);
X = zeros(1, Nsteps);
for s = 1:Nsteps
    X(s) = sum(arr_time <= t(s)); % nr. of arrivals by time t(s)
end

% illustration
axis([0 Tmax 0 max(X)]);
hold on;
title('Poisson Couting Process');
xlabel('time')
ylabel('nr. of arrivals');
comet(t,X);


