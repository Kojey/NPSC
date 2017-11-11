fsize = 16;
fsmall = fsize-4;
lwidth = 2;

c = 108.31254;
a = -1.526537;
x = [20 30 40 50 60 70 80 90 100];
hf = figure();
y = [1.00 0.64 0.41 0.29 0.22 0.17 0.13 0.11 0.09];
plot(x,y,"ob","linewidth",lwidth,x,c*x.**a,":b");
hold on;

_r = 0.9944;%corr(x,y)**2;
p = polyfit(x,y,1);
f = sprintf("F(x) = %d$x^{%d}$", c,a);
_r = sprintf("$R^2$ = %d", 0.9761); 
text (31, 0.7, f, "fontsize", fsmall);
text (31, 0.65, _r, "fontsize", fsmall);

xlabel("Distance (cm)","fontsize", fsize);
ylabel("Illuminance ratio","fontsize", fsize);

grid on;
set(gca, "LineWidth", 1, "fontsize", fsmall);
set (hf, "visible", "off");
print (hf, "illuminance_distance.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex illuminance_distance");
open ("illuminance_distance.pdf");


