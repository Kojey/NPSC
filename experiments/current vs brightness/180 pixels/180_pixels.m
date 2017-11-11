fsize = 16;
fsmall = fsize-4;
lwidth = 2;

x = 0:10:100;
hf = figure();
current = [0.120 0.507 1.233 1.983 2.700 3.440 4.373 4.860 5.547 6.260 6.940];

r = corr(x,current)**2;
p = polyfit(x,current,1);

plot(x,current,"ob","linewidth",lwidth,x,p(1)*x+p(2),":b");
hold on;
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (11, 5.7, f, "fontsize", fsmall);
text (11, 5.3, r, "fontsize", fsmall);

xlabel("Brightness levels (\\%)","fontsize", fsize);
ylabel("Current (mA)","fontsize", fsize);
grid on;
set(gca, "linewidth", lwidth, "fontsize", fsize);
set (hf, "visible", "off");
print (hf, "current_brightness_180.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex current_brightness_180");
open ("current_brightness_180.pdf");


