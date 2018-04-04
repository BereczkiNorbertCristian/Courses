
%ex1
times=1:1:7;
temperatures=[13, 15, 20,14, 15, 13, 10];
m = length(times)-1;
a = ((m+1)* sum(times.*temperatures) - sum(times) * sum(temperatures)) / ((m+1).*sum(times.^2)-(sum(times))^2);
b = (sum(times.^2) .*sum(temperatures) - sum(times .*temperatures) * sum(times))/((m+1)*sum(times.^2)-sum(times)^2);
fi =@(x) a*x+b;

fprintf('This is approx for 8');
fi(8)

E = sum((temperatures-fi(times)).^2)

fplot(fi,[0,8]);
hold on;
plot(times,temperatures,'*');

clear();
clf();

temperatures = [0 10 20 30 40 60 80 100];
pressures = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133]
p = polyfit(temperatures,pressures,2);
polyval(p,45)

m = length(temperatures)-1;
a = ((m+1)* sum(temperatures.*pressures) - sum(temperatures) * sum(pressures)) / ((m+1).*sum(temperatures.^2)-(sum(temperatures))^2);
b = (sum(temperatures.^2) .*sum(pressures) - sum(temperatures .*pressures) * sum(temperatures))/((m+1)*sum(temperatures.^2)-sum(temperatures)^2);

interp_poly=polyfit(temperatures,pressures,m-1);

fi =@(x) a*x+b;
fi_p=@(x) polyval(p,x);
fi_interp=@(x) polyval(interp_poly,x)
fi(45)

fplot(fi,[0,100]);
hold on;
fplot(fi_p,[0,100]);
hold on;
fplot(fi_interp,[0,100]);
hold on;
plot(temperatures,pressures,'*');

% EX 3
clear();
clf();

xnodes=-3:0.4:3;
y=sin(xnodes);
P = polyfit(xnodes,y,4);
f_P=@(x) polyval(P,x);

fplot(f_P,[-3,3]);
hold on;
plot(xnodes,y,'*');

% EX 4

clear();
clf();

axis([0,3,0,5]);
[x,y]=ginput(10)

P = polyfit(x,y,2);
f_P=@(x) polyval(P,x);

fplot(f_P,[0,3]);
hold on;
plot(x,y,'*');

axis([0,3,0,5]);



