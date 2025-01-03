clear
close all

r = csvread("ntc.csv");

t = r(:,1);
a = r(:,2);

ad = 1024.*(a./(a+10));

p = polyfit(ad, t, 10);
ad2 = 0:1023;
t2 = round(polyval(p, ad2),1);

figure(1)
plot(ad,t)

figure(2)
plot(ad2,t2,'r')


dlmwrite('data.dlm',t2*10,',');