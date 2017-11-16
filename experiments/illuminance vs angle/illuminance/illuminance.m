fsize = 16;
fsmall = fsize-4;
lwidth = 2;

angle = [-90:30:90]';
distance = [20:10:100]';
hf = figure();
illuminance = [
1998 5310 5950 6420 5950 5310 1998;
547 3302 3770 4910 3770 3302 547;
149 1657 2354 2507 2354 1657 149;
110 1219 1620 1820 1620 1219 110;
60 892 1227 1375 1227 892 60;
55 691 943 1012 943 691 55;
43 547 785 810 785 547 43;
35 420 607 667 607 420 35;
30 353 500 557 500 353 30
];

%plot(x,y,"ob","linewidth",lwidth,x,c*x.**a,":b");
h=surf(angle,distance,illuminance);
rotate(h,[0 0 1],0);
hold on;


%_r = 0.9944;%corr(x,y)**2;
%p = polyfit(x,y,1);
%f = sprintf("F(x) = %d$x^{%d}$", c,a);
%_r = sprintf("$R^2$ = %d", 0.9761); 
%text (31, 0.7, f, "fontsize", fsmall);
%text (31, 0.65, _r, "fontsize", fsmall);

xlabel("Angle (degree)","fontsize", fsize);
ylabel("Distance (cm)","fontsize", fsize);
zlabel("Illuminance (lx)","fontsize", fsize);


grid on;
set(gca, "LineWidth", 1, "fontsize", fsmall);
set (hf, "visible", "off");
print (hf, "illuminance.pdf", "-dpdflatexstandalone");
set (hf, "visible", "on");
%system ("pdflatex illuminance");
%open ("illuminance.pdf");


