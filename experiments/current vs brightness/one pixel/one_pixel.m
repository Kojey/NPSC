x = 0:10:100;
hf = figure();
r = [3 4 5 7 8 10 11 13 14 15 17];
g = [3 4 5 7 8 10 11 12 14 15 17];
b = [3 4 5 6 8 9 11 12 13 15 16];
rgb = [3 5 9 13 17 22 26 30 34 38 42];
plot(x,r,"r",x,g,"g",x,b,"b",x,rgb,"k");
hold on;

_r = corr(x,r)**2;
p = polyfit(x,r,1);
f = sprintf("$F_{red}$(x) = %dx+%d", p(1),p(2));
_r = sprintf("$R_{red}^2$ = %d", _r); 
text (11, 45, f);
text (11, 41, _r);
_r = corr(x,g)**2;
p = polyfit(x,g,1);
f = sprintf("$F_{green}$(x) = %dx+%d", p(1),p(2));
_r = sprintf("$R_{green}^2$ = %d", _r); 
text (11, 35, f);
text (11, 31, _r);
_r = corr(x,b)**2;
p = polyfit(x,b,1);
f = sprintf("$F_{blue}$(x) = %dx+%d", p(1),p(2));
_r = sprintf("$R_{blue}^2$ = %d", _r); 
text (11, 25, f);
text (11, 21, _r);

xlabel("Brightness levels (\\%)");
ylabel("Current (mA)");
title ("Current drawn by one neopixel per colour brightness.");
legend("R","G", "B", "RGB");
grid on;
set(gca, "linewidth", 1, "fontsize", 12)
set (hf, "visible", "off");
print (hf, "current_brightness_1.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex current_brightness_1");
open ("current_brightness_1.pdf");


