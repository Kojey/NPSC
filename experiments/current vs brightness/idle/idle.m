x = [0 10 25 50 90 120 150 180];
hf = figure();
idle = [89 89 90 92 95 97 99 101];
plot(x,idle,"k");
hold on;


r = corr(x,idle)**2;
p = polyfit(x,idle,1);
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (11,99, f);
text (11, 98, r);


xlabel("Number of neopixels powered on");
ylabel("Idle current (mA)");
title ("Current drawn by the neopixels when in idle");
grid on;
set (hf, "visible", "off");
print (hf, "idle_current_180.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex idle_current_180");
open ("idle_current_180.pdf");


