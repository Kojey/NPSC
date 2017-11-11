fsize = 16;
fsmall = fsize-4;
lwidth = 2;

x = [0.09 0.49 1.24 1.95 3.38 4.1 5.35 6 6.55];
hf = figure();
temp = [2.176 6.417 11.750 17.667 28.083 29.667 39.000 43.091 44.750];


r = corr(x,temp)**2;
p = polyfit(x,temp,1);
plot(x,temp,"ob","linewidth",lwidth,x,p(1)*x+p(2),":b");
hold on;
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (0.5, 43, f, "fontsize", fsmall);
text (0.5, 38, r, "fontsize", fsmall);

xlabel("Current (A)", "fontsize", fsize);
ylabel("Temperature rise ($^oC$)", "fontsize", fsize);
grid on;
set(gca, "linewidth", lwidth, "fontsize", fsize);
set (hf, "visible", "off");
print (hf, "temp.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex temp");
open ("temp.pdf");


