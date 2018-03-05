
% Ex 1

x = 0:0.1:1;
l1 = polyval([1,0],x);
l2 = polyval([3/2,-(1/2),0],x);
l3 = polyval([5/2,0,-(3/2),0],x);
l4 = polyval([35/8,0,-(15/4),3/8,0],x);

subplot(2,2,1);plot(x,l1);
subplot(2,2,2);plot(x,l2);
subplot(2,2,3);plot(x,l3);
subplot(2,2,4);plot(x,l4);

clear;
clf;

% Ex 2a

t = -1:0.01:1;
T1 = cos(acos(t));
T2 = cos(2*acos(T1));
T3 = cos(3*acos(T2));

plot(t,T1);
hold on;
plot(t,T2);
hold on;
plot(t,T3);

clear;
clf;

% Ex 2b

x=-1:0.01:1;

n = 3;

for i=0:1:n
    plot(x,cheb(i,x));
    hold on;
end

clear;
clf;

x=-1:0.1:3;
n=6;
plot(x,exp(x),'LineWidth',3);
hold on;
for i=1:1:n
   plot(x,taylor(i,x));
   hold on;
end

title('Taylor aproxinmation');

clear;
clf;

% Ex 4

h = 0.25;
ael = 1;
a = [];
for i=0:1:6
    a = [a,ael];
    ael = ael + h;
end

n = length(a);
res = zeros(n,n);
for i = 1:1:n
   res(i,1) = magic(a(1,i));
end

for j=2:1:n
   for i=1:1:n-j+1
      res(i,j) = res(i+1,j-1) - res(i,j-1); 
   end
end

res

clear;
clf;
% Ex 5

x = [2,4,6,8];
res = zeros(length(x))
res(1,1) = 4;
res(2,1) = 8;
res(3,1) = 14;
res(4,1) = 16;
n = length(x);

for j=2:1:n
   for i=1:1:n-j+1
      res(i,j) = (res(i+1,j-1) - res(i,j-1))/(x(1,i+j-1)-x(1,i)); 
   end
end

res

% FUNCTIONS -------------------

function f = magic(x)
    f = sqrt(5*x*x + 1);
end

function p = cheb(n,x)
    if n == 0
        p = ones(1,length(x));
    elseif n == 1
        p = x;
    else
        p = 2 * x .* cheb(n-1,x) - cheb(n-2,x);
    end
end

function t=taylor(n,x)
    sum = zeros(1,length(x));
    fact = 1;
    for i=0:1:n
        sum = sum + (x.^i)./(fact) * fc(0);
        fact = fact * (i+1);
    end
    t=sum;
end

function f=fc(x)
    f = exp(x);
end




