% xnodes = [1930 1940 1950 1960 1970 1980];
% f = [123203 131669 150697 179323 203212 226505];
xnodes = [81,100,121,144,169];
f = [9,10,11,12,13];
x = 115;


res = Lagrange(xnodes,f,x);
fprintf("Result is %6.2f\n",res);
fprintf("True is %6.2f",sqrt(115));

clear();

xnodes = linspace(0,10,21);
ynodes = zeros(1,21);
for i=1:21
   ynodes(i) = (1 + cos(pi*xnodes(i)))/(1+xnodes(i));
end
x=0:0.01:10;
y=zeros(1,length(x));
for i=1:length(x)
   if(ismember(x(i),xnodes))
        y(i) = (1+cos(pi*x(i)))/(1+x(i));
   else
        y(i)=Lagrange(xnodes,ynodes,x(i));
   end
end
plot(xnodes,ynodes,'*');
hold on;
funcx = zeros(1,length(x));
for i=1:length(x)
    funcx(i) = (1 + cos(pi*x(i)))/(1+x(i));
end
plot(x,funcx,'Color','g');
hold on;
plot(x,y,'Color','r');

legend('Noduri','Lagrange','Function')


function res=Lagrange(xnodes,f,x)
    s1 = 0;
    s2 = 0;

    n=length(xnodes);
    for i=1:1:n
        s1 = s1 + (Ai(xnodes,xnodes(i),i)*f(i))/(x-xnodes(i));
        s2 = s2 + Ai(xnodes,xnodes(i),i)/(x-xnodes(i));
    end
    res=s1/s2;
end

function z=Ai(xnodes,x,i)
    prod = 1;
    n=length(xnodes);
    for j=1:1:n
       if(i~=j)
           prod = prod * (x-xnodes(j));
       end
    end
    z=1/prod;
end