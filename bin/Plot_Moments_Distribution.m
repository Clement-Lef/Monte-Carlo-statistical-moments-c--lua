format long;

% This file plots the moments distribution and fits a Gaussian to the data. If enough moments have been computed
% (~500-1000), then according to the central limit theorem the fit should be appropriate.

% Load the file in which the moments have been written
Moments = load('../README/Moment_order_1_f_x_equal_x_square_uniform_between_0_and_1');

% Number of beans to display a histogram and to compute the occurences of
% the moments           CHANGE IF TOO MUCH OR TO FEW
nbins = round(5*log(length(Moments)));

% Actual bins (must be a column vector to plot)
bins = transpose(linspace(min(Moments),max(Moments),nbins));
% Occurences for each bin
occurences = zeros(length(bins),1);
% Computing the occurences : 
for i=1:length(Moments)
    for bin=1:length(bins)-1
        if ((Moments(i) >= bins(bin)) && Moments(i) < bins(bin+1))
            occurences(bin) = occurences(bin) +1;
        end
    end
end
% Add the occurence of the maximum moment (not taken in account in the loop)
occurences(end) = occurences(end) +1;

% gaussian fit to the occurences to verify Central Limit Theorem
gaussian = fit(bins, occurences,'gauss1');
gaussian_coefficients = coeffvalues(gaussian);

figure
% The moments are shifted of 1/2 bin, so that bins are centered on the
% value (Matlab default is left corner aligned on the value)
h = histogram(Moments+0.5*(bins(1)-bins(2)),nbins);
hold on;
bins_grid = linspace(bins(1), bins(end), 100*length(bins));
p = plot(bins_grid, gaussian(bins_grid),'-r');
xlabel('Moment values');
ylabel('Occurences');
title('Moments distribution');
legend([h p],'Moment occurences','Gaussian fit')
dim = [0.15 0.71 0.2 0.2];
str = {'Gaussian parameters : ',['\mu = ' num2str(gaussian_coefficients(2))],...
       ['\sigma = ',num2str(gaussian_coefficients(3)/sqrt(2))]};
annotation('textbox',dim,'String',str,'FitBoxToText','on');