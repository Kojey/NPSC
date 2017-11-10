x = 0:10:100;
hf = figure();
current = [0.120 0.507 1.233 1.983 2.700 3.440 4.373 4.860 5.547 6.260 6.940];
plot(x,current,"b");
hold on;

r = corr(x,current)**2;
p = polyfit(x,current,1);
f = sprintf("F(x) = %dx+%d", p(1),p(2));
r = sprintf("$R^2$ = %d", r); 
text (11, 5.7, f);
text (11, 5.5, r);

xlabel("Brightness levels (\\%)");
ylabel("Current (mA)");
title ("Current drawn by the Ring per colour brightness.");
grid on;
set (hf, "visible", "off");
print (hf, "current_brightness_180.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex current_brightness_180");
open ("current_brightness_180.pdf");


