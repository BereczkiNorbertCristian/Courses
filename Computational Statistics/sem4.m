
% P1
% homog Markov chain

P = [ 0.4 0.6; 0.6 0.4];
% a)
% 5:30 initial time  t = 0, X0
P0 = [ 1 0 ];
% 8:30 3 hours later, 3 times later
% P^(3)_{1,1},p^(3)_{1,2} = ?
% P^(3)_{1,1} = P(X3=1 | X0=1)
% P^(3) = P^3

P3 = P^3;

% b)
% St-state distr
% PI*P=PI
% SIGMA * PI_{k}=1
% check notebook

% P2
clear();

P = [ 0.6 0.4 ; 0.2 0.8];
% homog. M. chain
P0 = [ 0 1 ];
P2 = P0 * P^2;

% P3
clear();
% homog. again
P = [ 0.6 0.4 ; 0.3 0.7 ];
P0 = [ 1 0 ];
P2 = P0 * P^2;

% b) Compute the st-state distribution
% on notebook

% P4
clear();

% a)
A0 = binopdf(0:2, 2, 0.2);
% We have 1 connected user
A1 = [ 0.4 0.5 0.1];
A2 = binopdf(2:-1:0, 2, 0.5);
P = [ A0 ; A1 ; A2 ];

% b)
P0 = [ 0 0 1 ];
P1 = P0 * P^2;
ans = P1(2);

% c)
% Let's setup like Ax=b
A = [ P' - eye(3); [ 1 1 1]];
b = [ 0; 0; 0; 1];
X = A\b;

% expected value of E(X120) approx by PI
E = 0.4082 + 2* 0.0816;
E = [ 0 1 2 ] * X;

% P5
clear();
P = [ 0.7 0.3 ; 0.4 0.6 ];
% a) steady state
pi = [ 4/7 3/7 ];

% b)
P0 = [ 0.2 0.8 ];
% Simulate Problem 5 Seminar 4 b),c)
Nm = input('length of sample path=');
N = input('number of simulations=');
for j = 1 : N
    P0 = [ 0.2 0.8 ]; % initial situation of sunny/rainy
    P = [ 0.7 0.3 ; 0.4 0.6]; % trans. prob. matrix
    P1(j,:) = P0; % P1 contains the forecast in day t = 1
    for t = 1 : Nm
        U = rand;
        X(t) = 1 * ( U < P0(1) ) + 2 * ( U >= P0(1) );
        % Gen. X(t) as a Bern(P0(1)).
        P1(t+1,:) = P1(t,:) * P; % P_{t+1} = T_{t} * P => the forecast for the next day
        P0 = P(X(t),:);
    end
    % c) Find long streaks of sunny/rainy days
    ichange = [ find(X(1:end-1)~=X(2:end)) , Nm ];
    % indices where states change
    %longstr. a vector of long streaks of sunny or rainy
    longstr(1) = ichange(1);
    for i = 2 : length(ichange)
        longstr(i) = ichange(i) - ichange(i-1);
    end
    %fprintf('\n streaks of sunny/rainy:\n');
    %fprintf(num2str(longstr));
    if(X(1) == 1)
        sunny = longstr(1:2:end);
        rainy = longstr(2:2:end);
    else
        sunny = longstr(2:2:end);
        rainy = longstr(1:2:end);
    end
    maxs(j) = max(sunny);
    maxr(j) = max(rainy); % longest streaks
    fprintf('\n');
end

fprintf('\n prob. of water shortage is %1.4f\n', mean(maxs >= 7));
fprintf('\n prob. of flooding is %1.4f\n', mean(maxr >= 7));




