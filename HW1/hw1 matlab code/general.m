%% Math G4077 - Homework Assignment 1 - Fall 2012

% Student: Julian R. Siri
% UNI: jrs2220
clc
clear all
%% General Inputs
S_0 = 100;      % initial asset price
vol = 0.3;      % asset's volatility
r = 0.05;       % constant risk-free interest rate
d = 0.02;       % dividend yield
K = 110;        % strike price
T = 1;          % maturity, in years

%% Problems

% a. Use the closed-form formulae to compute the prices for a
% European-style call and put.
disp('Answers to part a)');
Call_Price_a = callput(S_0,K,vol,r,T,d,'Call');
str = fprintf('Call Option price using closed-form formula = %g. \n',...
    Call_Price_a);

Put_Price_a = callput(S_0,K,vol,r,T,d,'Put');
str = fprintf('Put Option price using closed-form formula = %g. \n',...
    Put_Price_a);

clear str;

% b. Use the analytic solution and Monte Carlo simulation to compute the
% prices for a European-style call and put.
I = 10000;   % number of paths

fprintf('\n');
disp('Answers to part b)');
Call_Price_b = exactSDE(S_0,K,vol,r,T,d,I,'Call');
str = fprintf('Call Option price using single-step exact SDE solution = %g. \n',...
    Call_Price_b);

Put_Price_b = exactSDE(S_0,K,vol,r,T,d,I,'Put');
str = fprintf('Put Option price using single-step exact SDE solution = %g. \n',...
    Put_Price_b);

clear str I;
% c. Use the Euler numerical solution to dS(t) = (r - d)dt + sigma*dW(t))
% and Monte Carlo simulation to compute the prices for a European-style
% call and put.
I = 252;        % time steps per year
J = 10000;      % number of paths

fprintf('\n');
disp('Answers to part c)');
Call_Price_c = EulerSol(S_0,K,vol,r,T,d,J,I,'Call');
str = fprintf('Call Option price using Euler numerical solution of SDE for spot = %g. \n',...
    Call_Price_c);

Put_Price_c = EulerSol(S_0,K,vol,r,T,d,J,I,'Put');
str = fprintf('Put Option price using Euler numerical solution of SDE for spot = %g. \n',...
    Put_Price_c);

clear str I J;

% d. Use the Euler numerical solution to dlogS(t) = (r - d - sigma^2/2)dt +
% sigma*dW(t), and Monte Carlo simulation to compute the prices for a
% European-style call and put.
I = 252;        % time steps per year
J = 10000;      % number of paths

fprintf('\n');
disp('Answers to part d)');
Call_Price_d = EulerdlogSol(S_0,K,vol,r,T,d,J,I,'Call');
str = fprintf('Call Option price using Euler numerical solution of SDE for log spot = %g. \n',...
    Call_Price_d);

Put_Price_d = EulerdlogSol(S_0,K,vol,r,T,d,J,I,'Put');
str = fprintf('Put Option price using Euler numerical solution of SDE for log spot = %g. \n',...
    Put_Price_d);

clear str I J;

% e. Use the Milstein solution to dS(t) = S(t)((r-d)dt + sigma*dW(t)), and
% Monte Carlo simulation to compute the prices for a European-style call
% and put.
I = 252;        % time steps per year
J = 10000;      % number of paths

fprintf('\n');
disp('Answers to part e)');
Call_Price_e = MilsteinSDE(S_0,K,vol,r,T,d,J,I,'Call');
str = fprintf('Call Option price using Milstein numerical solution of SDE for spot = %g. \n',...
    Call_Price_e);

Put_Price_e = MilsteinSDE(S_0,K,vol,r,T,d,J,I,'Put');
str = fprintf('Put Option price using Milstein numerical solution of SDE for spot = %g. \n',...
    Put_Price_e);

clear str I J;

% f. Benchmarking results against MATLAB toolboxes

% For the closed-form solution
fprintf('\n');
disp('---  BENCHMARKING AGAINST MATLAB TOOLBOXES  ---');
[Closed_form_call, Closed_form_put] = blsprice(S_0,K,r,T,vol,d);
fprintf('\n');
fprintf('The difference for part a) is %g for the call and %g for the put \n',...
    Call_Price_a - Closed_form_call,Put_Price_a - Closed_form_put);
fprintf('between the BS pricer included in Matlab and the script produced \n');
