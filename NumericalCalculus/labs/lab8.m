
% Ex 1
a=1;
b=1.5;
n=500;
f=@(x) exp(-(x.^2));
ans=(b-a)*(f((a+b)/2))

pts = linspace(a+(b-a)/(2*n),b-(b-a)/(2*n),n);
ans=((b-a)/(n)) * sum(f(pts))

% Ex 2
clear();

a=0;
b=1;
pts=[a,b];
epsil=10^(-5);
ok=1;
while ok>0
    ok=0;
    n=length(pts);
    div_pts=[pts,(pts(1:(n-1))+pts(2:n))./2];
    div_pts=sort(div_pts);
    sm_pts=trap_lst(pts)
    sm_div_pts=trap_lst(div_pts)
    if(abs(sm_pts-sm_div_pts) > epsil)
        ok=1
    end
    pts=div_pts;
end

% Ex 3
fprintf("EXERCITIUL 3")
clear();

a=0;
b=1;
pts=[a,b];
epsil=10^(-5);
ok=1;
h=b-a;
Qs0=(h/6)*(fc(a)+4*fc(a+h/2)+fc(b));
iter=1;
while ok>0
    ok=0;
    n=length(pts);
    div_pts=[pts,(pts(1:(n-1))+pts(2:n))./2];
    div_pts=sort(div_pts);
    div_pts=div_pts;
    sm_pts=trap_lst(pts);
    sm_div_pts=trap_lst(div_pts);
    Qs1=-1;
    if(iter > 1)
        Qs1=(1/3)*(4*sm_div_pts - sm_pts)
    else
        ok=1;
    end
    if(ok==1 || abs(Qs1-Qs0) > epsil)
        ok=1;
    end
    pts=div_pts;
    Qs0=Qs1;
    iter=iter+1
end
ans=Qs0
fprintf("GATA\n");

% Ex 4

fprintf("ex 4")
clear();

a=1;
b=3;
f=@(x) (100./(x.*x)).*sin(10./x);
err=10^(-4);
pts=linspace(a,b,100);
plot(pts,f(pts));

ans=adquad(a,b,err,f)

fprintf("GATA 4\n");

function res=Simpson(a,b,f)
    h=b-a;
    res=(h/6)*(f(a)+4*f(a+h/2)+f(b));
end

function res=adquad(a,b,err,f)
    I1=Simpson(a,b,f);
    I2=Simpson(a,(a+b)/2,f)+Simpson((a+b)/2,b,f);
    if(abs(I1-I2)<15*err)
        res=I2;
    else
        res=adquad(a,(a+b)/2,err,f)+adquad((a+b)/2,b,err,f);
    end
end

function res=fc(x)
    res= 2./(1+x.^2);
end

function res=trap(x,y)
    res=((y-x)/2) * (fc(x) + fc(y));
end

function res=trap_lst(lst)
    ln=length(lst);
    sm = 0;
    for i=1:ln-1
        sm = sm + trap(lst(i),lst(i+1));
    end
    res=sm;
end



