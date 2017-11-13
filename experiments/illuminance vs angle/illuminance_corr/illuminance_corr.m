fsize = 16;
fsmall = fsize-4;
lwidth = 2;

x = 20:10:100;
hf = figure();

f = 108.313*x.**(-1.52654);
g = 400*x.**(-2);
plot(x,f,"r","linewidth",lwidth,x,g,"g","linewidth",lwidth);
hold on;


r = corr(f,g);
r = sprintf("Corr(f(x),g(x)) = %d", r); 
text (50, 1.1, r, "fontsize", fsmall);

xlabel("Illuminance ratio ","fontsize", fsize);
ylabel("Distance (cm)","fontsize", fsize);
legend("Experimental model","Theoretical model");
grid on;
set(gca, "linewidth", lwidth, "fontsize", fsize)
set (hf, "visible", "off");
print (hf, "illuminance_corr.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex illuminance_corr");
open ("illuminance_corr.pdf");


