xndoes = [0 3 5 8 13];
dists = [0 225 383 623 993];
speeds = [75 77 80 74 72];

xnodes_d = [0 0 3 3 5 5 8 8 13 13];
dists_d = [0 0 225 225 383 383 623 623 993 993];
speeds_d = [75 75 77 77 80 80 74 74 72 72];

first_row = Compute_Row(xnodes_d,dists_d,speeds_d)
answ = Newton_Approx(xnodes_d,dists_d,10,first_row)

clear();

xnodes_d = [1 1 2 2];
dists_d = [0 0 0.6931 0.6931];
speeds_d = [1 1 0.5 0.5];

first_row = Compute_Row(xnodes_d,dists_d,speeds_d)
answ = Newton_Approx(xnodes_d,dists_d,1.5,first_row)

clear();

xs = linspace(-5,5,100);
xnodes = linspace(-5,5,15);
f = sin(2.*xnodes);
fd = 2.*cos(2.*xnodes);
herm_lst = zeros(1,length(xs));
for i=1:length(xs)
    herm_lst(i) = HermiteApprox(xnodes,f,fd,xs(i));
end

ys = sin(2.*xs);

plot(xnodes,f,'*');
hold on;
plot(xs,ys);
hold on;
pause;
plot(xs,herm_lst);

% FUNCTIONS

function res=HermiteApprox(xnodes,f,fd,t)
    xnodes_d = DoubleList(xnodes);
    dists_d = DoubleList(f);
    speeds_d = DoubleList(fd);
    first_row = Compute_Row(xnodes_d,dists_d,speeds_d);
    answ = Newton_Approx(xnodes_d,dists_d,t,first_row);
    res=answ
end

function res=DoubleList(lst)
    
    new_lst = [];
    for i=1:length(lst)
       new_lst = [new_lst,lst(i)]; 
       new_lst = [new_lst,lst(i)];
    end
    res=new_lst;
end

function ans=Compute_Row(x,f,fd)
n = length(x);
res = zeros(n);
res(:,1) = f;

for j=2:1:n
   for i=1:1:n-j+1
      if((j == 2) && mod(i,2)==1)
         res(i,j) = fd(i);
      else
        res(i,j) = (res(i+1,j-1) - res(i,j-1))/(x(1,i+j-1)-x(1,i)); 
      end
   end
end
ans=res(1,2:n);
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
