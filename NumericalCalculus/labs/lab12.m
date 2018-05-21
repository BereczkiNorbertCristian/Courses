
% Ex 3

N = 100;
a = 1;
b = 2;
f = @(x) (x-2)^2 - log(x);
err = 10^(-4);

% FZERO represents the result we are looking for
res1 = fzero(f,1)
res2 = bisect(f,a,b,N,err)
% assert(abs(fzero(f,1)-bisect(f,a,b,N,err)) < 0.0001);

% ------------------------
% Ex 4
clear();

f = @(x) cos(x);
N = 100;
a = 0.5;
b = pi/4;
err = 10^(-4);
res1 = fzero(f,1)
res2 = false_position(f,a,b,N,err)

% ----------------------
% Ex 2

x0 = 1;
x1 = 2;
N = 100;
err = 10^(-4);
f = @(x) x^3-x^2-1;

res1 = fzero(f,0)
res2 = secant_method(f,x0,x1,N,err)

% Ex 1

x0 = pi/4;
N = 100;
err = 10^(-4);
f = @(x) cos(x);

res1 = fzero(f,1)
res2 = newton(f,x0,N,err)


function res=bisect(f,a,b,N,err)
    itr = 0;
    while(itr < N && (abs(a-b)/abs(a)) > err)
       c = (a + b) / 2;
       prod = f(c)*f(b);
       if(prod < 0)
           a = c;
       else
           b = c;
       end
       itr = itr + 1;
    end
    res = (a+b)/2;
end

function res=false_position(f,a,b,N,err)
    itr = 0;
    while(itr < N && (abs(a-b)/abs(a)) > err)
       c = (a*f(b) - b*f(a)) / (f(b) - f(a));
       prod = f(a)*f(c);
       if(prod < 0)
           b = c;
       else
           a = c;
       end
       itr = itr + 1;
    end
    res = (a+b)/2;
end

function res=secant_method(f,x0,x1,N,err)
    itr = 0;
    while(itr < N && (abs(x1-x0)/abs(x1)) > err)
       x2 = x1 - f(x1) * ((x1-x0)/(f(x1)-f(x0)));
       itr = itr + 1;
       x0 = x1;
       x1 = x2;
    end
    res = x1;
end

function res=newton(f,x0,N,err)
    itr = 0;
    x1 = 1000;
    while(itr < N)
       x1 = x0 - f(x0)/(-sin(x0));
       itr = itr + 1;
       if(abs(x1-x0) < err)
        break;
       end
       x0 = x1;
    end
    res = x0;
end



