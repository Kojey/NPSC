x_avg = [1.000	0.909	0.679	0.079	0.000	0.000	0.000	0.000	0.000	0.079	0.679	0.909 1];
x_min = [1.000	0.851	0.590	0.033	0.000	0.000	0.000	0.000	0.000	0.033	0.590	0.851
];
x_max = [1.000	0.967	0.769	0.124	0.000	0.000	0.000	0.000	0.000	0.124	0.769	0.967
];
hf = figure();
current = [0.120 0.507 1.233 1.983 2.700 3.440 4.373 4.860 5.547 6.260 6.940];
t = 0:pi/6:2*pi
polar(t,x_avg,"g");
view([270 90]);
hold on;

set (gca, "rtick", 0.1:0.1:1);
title ("Current drawn by the Ring per colour brightness.");
grid on;
set (hf, "visible", "off");
print (hf, "current_brightness_180.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
system ("pdflatex current_brightness_180");
open ("current_brightness_180.pdf");


