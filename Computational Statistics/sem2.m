% Simulate Bern(p) distr.

%p = input('p(in(0,1))=');
p=0.6
U = rand;
X = U < p;
%N = input('Nr. of simulations='); % size of the Monte Carlo study
% try 10, 1e3, 1e5
N=1000;
for i=1:N
   U = rand;
   X(i) = U < p;
end
% Compare it to the Bern(p) distr.
UX = unique(X);
nX = hist(X, length(UX));
rel_freq = nX / N; % approx the prob.

clf;
% Simulate Binomial of (n,p)

n = 1000;
p = 0.5;

U = rand(n, 1);
X = sum( U < p);

%N = input('Nr. of simulations in binomial:')
N = 1000;

for i=1:N
   U = rand(n, 1);
   X(i)=sum( U < p );
end

UX = unique(X);
nX = hist(X, length(UX));
rel_freq = nX / N; % approx the prob.

%Compare to the binomial distr graphically
k = 0:n;
pk = binopdf(k,n,p);
plot(k, pk, '*', UX, rel_freq, 'ro');
legend('Bino distr.', 'Simulation')

clf;
% Simulate Geometric Distribution

p = 0.4;
X = 0; % init. nr. of failures
while rand >= p % count nr. of failures
    X = X + 1;
end
N = 1000;
for i=1:N
   X(i) = 0;
   while rand <= p
       X(i) = X(i) + 1;
   end
end

UX = unique(X);
nX = hist(X, length(UX));
rel_freq = nX / N; % approx the prob.

k = 0:50;
pk = geopdf(k, p);
plot(k, pk, '*', UX, rel_freq, 'ro');

clf;
% Simulate Negative Binomial

p = 0.6;
n = 10; % rank of success (in N)

for j=1:n
    Y(j) = 0;
    while rand >= p
       Y(j) = Y(j) + 1; 
    end
end
X = sum(Y);
N = 1000;
for i = 1:N
    for j=1:n
        Y(j) = 0;
        while rand >= p
            Y(j) = Y(j) + 1; 
        end
    end
    X(i) = sum(Y);
end


UX = unique(X);
nX = hist(X, length(UX));
rel_freq = nX / N; % approx the prob.

k = 0:20;
pk = nbinpdf(k, n, p);
plot(k, pk, '*', UX, rel_freq, 'ro');
legend('Neg bino distr.', 'Simulation');

clf;
% Simulate Poiss(lambda) distr.

%lambda = input('lambda (>0)='); % par
lambda = 10
i = 0;
U = rand;
F = exp(-lambda); % init. value F cdf
while U >= F
   i = i + 1;
   F = F + exp(-lambda) * (lambda^i)/gamma(i+1);
end
X = i;

N = 1000
for j = 1:N
    i = 0;
    U = rand;
    F(j) = exp(-lambda); % init. value F cdf
    while U >= F(j)
        i = i + 1;
        F(j) = F(j) + exp(-lambda) * (lambda^i)/gamma(i+1);
    end
    X(j) = i;
end

UX = unique(X);
nX = hist(X, length(UX));
rel_freq = nX / N; % approx the prob.

k = 0:20;
pk = poisspdf(k, lambda);
plot(k, pk, '*', UX, rel_freq, 'ro');
legend('Poiss distr.', 'Simulation');



