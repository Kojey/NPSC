fsize = 16;
fsmall = fsize-4;
lwidth = 2;


x = [0 10 25 50 90 120 150 180];
hf = figure();
idle = [89 89 90 92 95 97 99 101];

r = corr(x,idle)**2;
p = polyfit(x,idle,1);

plot(x,idle,"ob","linewidth",lwidth,x,p(1)*x+p(2),":b");
hold on;
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (11,99, f, "fontsize", fsmall);
text (11, 97, r, "fontsize", fsmall);


xlabel("Number of neopixels powered on","fontsize", fsize);
ylabel("Idle current (mA)","fontsize", fsize);
grid on;
set(gca, "linewidth", lwidth, "fontsize", fsize);
set (hf, "visible", "off");
print (hf, "idle_current_180.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex idle_current_180");
open ("idle_current_180.pdf");


