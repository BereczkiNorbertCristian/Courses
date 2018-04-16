% FIRST PROBLEM
a = 0;
b = 1;
f=@(x) 2./(1+x.*x);

integ_trapez = (b-a)/2 * (f(a) + f(b))
integ_simpson = (b-a)/6 * (f(a)+f(b)+4*f((a+b)/2))

xnodes = [0,0,1,1]
ynodes = [0,f(0),f(1),0]

pts = linspace(-1,2,100);
plot(pts,f(pts));
hold on;
plot(xnodes,ynodes);

clf();
clear();

% EX 2

a = 1.4;
b = 2;
c = 1;
d = 1.5;

f = @(x,y) log(x+2.*y);
prd = ((b-a)*(d-c)/16);
sm = f(a,c)+f(a,d)+f(b,c)+f(b,d);
sm2 =  2*f(a,(c+d)/2) + 2*f(b,(c+d)/2)+4*f((a+b)/2 ,(c+d)/2);
sm1 = 2*f((a+b)/2,c) + 2*f((a+b)/2,d);
sm2 = sm2 + sm1;
double_trapez = prd * (sm + sm2)

clear();
clf();

% EX 3


a = 0; b = 2*pi;
n = 10;
h = (b-a)/n;
x_pts = linspace(a+h,a+h*(n-1),n-1);
r=110;
p=75;
f=@(x) (1-(p./r).*(p./r).*sin(x)).^(1/2);
rep_trap = ((b-a)/(2*n)) * (f(a) + f(b) + 2*sum(f(x_pts)));
H = (60*r/(r*r-p*p)) * rep_trap

% EX 4

clear();
clf();  

M2f = 1;
f=@(x) (1./(12.*(x.*x.*x)))
f(10)
nds = [8 9 10 11 12]
f(nds)

a = 1; b = 2;
n = 10;
h = (b-a)/n;
x_pts = linspace(a+h,a+h*(n-1),n-1);

f=@(x) x.*log(x);
rep_trap = ((b-a)/(2*n)) * (f(a) + f(b) + 2*sum(f(x_pts)))

% EX 5

clear();
clf();


a = 0; b = pi;
n = 30;
h = (b-a)/n;
x_pts = linspace(a,a+h*(n),n+1);

f=@(x) 1./(4+sin(20.*x));
sm_in = x_pts(1:(n)) + x_pts(2:(n+1));
sm = 4.*(sum(f(sm_in./2)));
rep_simps_5 = ((b-a)/(6*n)) * (f(a) + f(b) + 2.*sum(f(x_pts(2:(n)))) + sm)

% EX 6

clear();
clf();
xval = 0.5;

f=@(x) exp(-(x.*x));
a = 0; b = xval;
n = 10;
h = (b-a)/n;
x_pts = linspace(a,a+h*(n),n+1);

sm_in = x_pts(1:(n)) + x_pts(2:(n+1));
sm = 4.*(sum(f(sm_in./2)));
erf_simps = ((b-a)/(6*n)) * (f(a) + f(b) + 2.*sum(f(x_pts(2:(n)))) + sm)
erf_6 = erf_simps * (2/(pi^(1/2)))
fprintf("%.10f\n",erf_6);

%EX 7 for extra point

a=0.1;
b=0.5;
c=0.01;
d=0.25;
f=@(x,y) exp(y./x);
n=10;
m=10;

h = (b-a)/(2*n);
j1= 0;j2=0;j3=0;
for i=0:2*n
   x=a+i*h;
   h1=(d-c)/(2*m);
   k1 = f(x,c) + f(x,d);
   k2 = 0;
   k3 = 0;
   for j=1:(2*m-1)
      y = c + j * h1;
      z=f(x,y);
      if(mod(j,2)==0)
            k2=k2+z;
      else
            k3=k3+z;
      end
   end
   l=(k1+2*k2+4*k3)*h1/3;
   if(i==0 || i==2*n)
       j1=j1+l;
   else
       if(mod(i,2)==0)
           j2=j2+l;
       else
           j3=j3+l;
       end
   end
end
J=(j1+2*j2+4*j3)*h/3;
fprintf("%.10f\n",J);

