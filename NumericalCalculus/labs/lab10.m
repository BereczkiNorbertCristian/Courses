
A=[1 1 1 1;
    2 3 1 5;
    -1 1 -5 3;
    3 1 7 -2];
b = [10;31;-2;18];
GE(A,b)
clear()

A = [6 2 1 -1
2 4 1 0
1 1 4 -1
-1 0 -1 3]
b=[8;7;5;1]

[L,U,P] = lu(A)
z = forwardsub(L,P*b)
x = backsub(U,z)

bb = A*x

function x=forwardsub(U,z)
    n = length(z);
    x = zeros(n,1);
    for i=1:n
       x(i) = (z(i)-U(i,:)*x) / (U(i,i)); 
    end
end

function x=backsub(U,z)
    n = length(z);
    x = zeros(n,1);
    for i=n:-1:1
       x(i) = (z(i)-U(i,:)*x) / (U(i,i)); 
    end
end

function x=GE(A,b)
    n = length(b);
    for p=1:n-1
       [mx,q] = max(abs(A(p:n,p)));
       q = q + p - 1;
       A([p q],:)=A([q p],:);
       b([p q])=b([q p]);
       for j=p+1:n
            m = A(j,p) / A(p,p);
            A(j,:) = A(j,:) - A(p,:).*m;
            b(j) = b(j) - b(p) .* m;
       end
    end
    x=zeros(n,1);
    x(n)=b(n)/A(n,n);
    for i=n-1:-1:1
       rs = A(i,i+1:n) * x(i+1:n)
       x(i) = (b(i)-rs) / A(i,i)
    end
end