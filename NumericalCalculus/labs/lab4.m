xnodes = 1:1:5;
f = [22,23,25,30,28];
ans = Newton_Approx(xnodes,f,2.5,Compute_Row(xnodes,f))

plot(xnodes,f,'*');
hold on;
newton_arr = linspace(1,5,100);
newton_res = zeros(1,length(newton_arr));
for i=1:length(newton_arr)
   newton_res(i) = Newton_Approx(xnodes,f,newton_arr(i),Compute_Row(xnodes,f));
end
plot(newton_arr,newton_res);
title('Newton Approximation');
legend('Nodes','Newton');

% Ex 2
clf();
clear();

xnodes = linspace(0,6,13);
f = exp(sin(xnodes));

plot(xnodes,f,'*');
hold on;
new_nodes = linspace(0,6,100);
func = exp(sin(new_nodes));
newton_poly=zeros(1,length(new_nodes));
first_row = Compute_Row(xnodes,f);
for i=1:length(new_nodes)
   newton_poly(i) = Newton_Approx(xnodes,f,new_nodes(i),first_row);
end
plot(new_nodes,func);
hold on;
plot(new_nodes,newton_poly);
title('Exercise 2');
legend('Interpolation points','Function','Newton approximation');

% Ex 3

clear();
clf();

xnodes = [81,100,121,144,169];
n=length(xnodes);
x=115;
% SORT
xnodes=Dummy_Sort(xnodes,x);
ynodes = sqrt(xnodes);

f=Calc_Atkin_Table(xnodes,ynodes,x)

Calc_Atkin(f,n)

% Ex fac1

clear();
xnodes=linspace(-5,5,20);
ynodes=sin(xnodes);
new_nodes=linspace(-5,5,100);
new_nodes_y=sin(new_nodes);
n=length(new_nodes);
atkin_app = zeros(1,n);
for i=1:n
   x=new_nodes(i);
   xnds=Dummy_Sort(xnodes,x);
   f=Calc_Atkin_Table(xnodes,ynodes,x);
   atkin_app(i) = Calc_Atkin(f,length(xnodes));
end

plot(xnodes,ynodes,'*');
hold on;
plot(new_nodes,new_nodes_y);
hold on;
plot(new_nodes,atkin_app);


% FUNCTIONS

function res=Calc_Atkin(f,n)
epsi = 0.001;
found = 0;
for i=2:n
   if(abs(f(i,i)-f(i-1,i-1)) <= epsi)
       res = f(i,i);
       found = 1;
       break;
   end
end

if(found == 0)
   res=sin(x);
end
end

function res=Calc_Atkin_Table(xnodes,ynodes,x)
n=length(xnodes);
f = zeros(length(xnodes));
f(:,1) = ynodes;
for j=1:n
   for i=(j+1):n
       f(i,j+1) = (f(j,j)*(xnodes(i)-x) - f(i,j)*(xnodes(j)-x)) / (xnodes(i)-xnodes(j));
   end
end
res=f;
end

function res=Dummy_Sort(xnodes,x) 
n=length(xnodes);
for i=1:n-1
    for j=i+1:n
       if(abs(xnodes(i)-x) > abs(xnodes(j)-x))
          aux = xnodes(i);
          xnodes(i) = xnodes(j);
          xnodes(j) = aux;
       end
    end
end
res=xnodes;
end

function res=Newton_Approx(xnodes,f,x,first_row)
    n=length(xnodes)-1;
    sum = f(1);
    for i=1:n
       prod = 1;
       for j=1:i
            prod = prod * (x-xnodes(j));
       end
       sum = sum + first_row(i)*prod;
    end
    res = sum;
end

function ans=Compute_Row(x,f)
n = length(x);
res = zeros(n);
res(:,1) = f;

for j=2:1:n
   for i=1:1:n-j+1
      res(i,j) = (res(i+1,j-1) - res(i,j-1))/(x(1,i+j-1)-x(1,i)); 
   end
end
ans=res(1,2:n);
end

