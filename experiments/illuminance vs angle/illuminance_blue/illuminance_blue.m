fsize = 16;
fsmall = fsize-4;
lwidth = 2;

x = [20 30 40 50 60 70 80 90 100];
hf = figure();
y_0 = [6420 4910 2507 1820 1375 1012 810 667 557];
y_30 = [5950 3770 2354 1620 1227 943 785 607 500];
y_60 = [5310 3302 1657 1219 892 691 547 420 353 ];
y_90 = [1998 547 149 110 60 55 43 35 30];
plot(x,y_0,"k","linewidth",lwidth,x,y_30,"y","linewidth",lwidth,x,y_60,"m","linewidth",lwidth,x,y_90,"c","linewidth",lwidth);
hold on;

xlabel("Distance (cm)","fontsize", fsize);
ylabel("Illuminance (lx)","fontsize", fsize);
legend("$0^o$","$30^o$","$60^o$","$90^o$")
grid on;
set(gca, "LineWidth", 1, "fontsize", fsmall);
set (hf, "visible", "off");
print (hf, "illuminance_blue.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex illuminance_blue");
open ("illuminance_blue.pdf");


