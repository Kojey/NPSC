x = [0.09 0.49 1.24 1.95 3.38 4.1 5.35 6 6.55];
hf = figure();
temp = [2.176 6.417 11.750 17.667 28.083 29.667 39.000 43.091 44.750];
plot(x,temp);
hold on;

r = corr(x,temp)**2;
p = polyfit(x,temp,1);
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (0.5, 43, f);
text (0.5, 40, r);

xlabel("Current (A)");
ylabel("Temperature rise ($^oC$)");
title ("Board temperature rise vs current drawn.");
grid on;
set (hf, "visible", "off");
print (hf, "temp.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex temp");
open ("temp.pdf");


