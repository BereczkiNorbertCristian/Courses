% EX 1
A = [400 -201;-800 401];
b = [200;-200];
x = A\b;

cond(A);

A_pert = [401 -201;-800 401];
b = [200;-200];
x_pert = A_pert\b;

rel_err_A = norm(A-A_pert) / norm(A)
rel_err_x = norm(x - x_pert) / norm(x_pert)
cond_number = rel_err_x / rel_err_A
cond(A)


clear();
% Ex 2
% a
A = [10 7 8 7;7 5 6 5;8 6 10 9;7 5 9 10];
b = [32;23;33;31];
x = A\b
cond(A)
% b
b_tilda = [32.1;22.9;33.1;30.9];
x_tilda = A\b_tilda
rel_err_b = norm(b - b_tilda)/norm(b)
rel_err_x = norm(x - x_tilda)/norm(x)
cond_computed = rel_err_x/rel_err_b
cond(A)
assert(cond_computed <= cond(A))
% c
A_pert = [10 7 8.1 7.2;
7.08 5.04 6 5;
8 5.98 9.89 9;
6.99 4.99 9 9.98];
x_pert = A_pert\b;
rel_err_A = norm(A-A_pert)/norm(A);
rel_err_x = norm(x-x_pert) / norm(x_pert);
cond_computed = rel_err_x / rel_err_A
cond(A)
assert(cond_computed <= cond(A))

% Ex 3
for i=10:15
   H = hilb(i);
   cond(H)
end

% Ex 4
% a
for i=10:15
   v=1./[1:i];
   V = vander(v);
   cond(V)
end
% b
for i=10:15
   v=(-1).*ones(1,i) + (2/i).*[1:i];
   V = vander(v);
   cond(V)
end