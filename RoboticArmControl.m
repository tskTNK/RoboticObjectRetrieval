
clear
clc

mode = 2; % imageTuning: 1, pickup: 2, position initialization: 4
serialControl = 1;
imageOutput = 1;
continuous = 1;

imageDetection = 0;
positionInitialization = 0;
alighDirection = 0;
pickupCompletion = 0;
operationCompletion = 0;
validControl = 0;

if serialControl == 1
    device = serialport("COM3",9600);
    readline(device)
%     device.Terminator
%     writeline(device,"h")
end

if mode == 1
    
    % back to default position
    openEndeffector(device);
    M2control = 785;
    M3control = 600;
    M4control = 530;
    armControl3D(device, M2control, M3control, M4control);
    readPotentiometer(device);

    disp('position Initialization done');
    pause(5); 
    
    for i = 1:1
        % Call "webcamlist" in the console to find what webcams you have

        % ans =
        % 2×1 cell array
        %     {'Integrated Webcam'}
        %     {'HD Web Camera'    }

        clear('cam'); % clear the cam object so you can make a new one
        cam = webcam('HD Web Camera'); % open the camera
        % preview(cam) % show preview

        % RGB = snapshot(cam); % Capture RGB image from Camera
        % figure(1)
        % imshow(RGB) % original
        % disp('Image is taken');

        RGB = snapshot(cam); % Capture RGB image from Camera
%         figure(1), imshow(RGB) % original
    %     disp('Image is taken');

        % Call "colorThresholder(RGB)" in the console to create a image mask
        % Find appropriate thresholds and export the setting
        % for more details,visit https://www.mathworks.com/help/images/image-segmentation-using-the-color-thesholder-app.html

        % Convert RGB image to chosen color space
        I = rgb2hsv(RGB);

        % Define thresholds for channel 1 based on histogram settings
        channel1Min = 0.925;
        channel1Max = 0.022;

        % Define thresholds for channel 2 based on histogram settings
        channel2Min = 0.202;
        channel2Max = 0.888;

        % Define thresholds for channel 3 based on histogram settings
        channel3Min = 0.700;
        channel3Max = 1.000;

        % Create mask based on chosen histogram thresholds
        sliderBW = ( (I(:,:,1) >= channel1Min) | (I(:,:,1) <= channel1Max) ) & ...
            (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
            (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
        BW = sliderBW;

        % Initialize output masked image based on input image.
        maskedRGBImage = RGB;

        % Set background pixels where BW is false to zero.
        maskedRGBImage(repmat(~BW,[1 1 3])) = 0;

%         figure(2), imshow(maskedRGBImage);
    %     disp('Image is masked');

        % Determine the connected areas and their centroid
        % https://www.mathworks.com/help/images/ref/bwconncomp.html is easier.

        CC = bwconncomp(sliderBW);
        s = regionprops(CC,'Centroid','Area');
        centroids = cat(1,s.Centroid);
        areas = cat(1,s.Area);
        [m,ind] = max(areas); % find the largest connected component 

        currentImageSize = m
        centroidR = centroids(ind,1)
        centroidC = centroids(ind,2)

        if CC.NumObjects == 0
            
            disp('no image detected');
            
            % back to nominal position
        else
            if imageOutput == 1
                    subplot(3,1,1), imshow(RGB)
                    subplot(3,1,2), imshow(maskedRGBImage)
                    subplot(3,1,3), imshow(double(sliderBW))
                    hold on
                    plot(centroids(ind,1),centroids(ind,2),'m*','markersize',32) 
                    hold off
            end
        end
    end    
          
end

if mode == 2
    
    if positionInitialization == 0
        
        % back to default position
        M2control = 785;
        M3control = 600;
        M4control = 530;
        armControl3D(device, M2control, M3control, M4control);
        readPotentiometer(device);
        openEndeffector(device);
                
        disp('position Initialization done');
        pause(5); 
            
        positionInitialization = 1;
    end
    
%     while(continuous)
    for i = 1:20
            
        % Call "webcamlist" in the console to find what webcams you have
        
        clear('cam'); % clear the cam object so you can make a new one
        cam = webcam('HD Web Camera'); % open the camera
        % preview(cam) % show preview
        
        % RGB = snapshot(cam); % Capture RGB image from Camera
        % figure(1)
        % imshow(RGB) % original
        % disp('Image is taken');
        
        RGB = snapshot(cam); % Capture RGB image from Camera
                
        % Call "colorThresholder(RGB)" in the console to create a image mask
        % Find appropriate thresholds and export the setting
        % for more details,visit https://www.mathworks.com/help/images/image-segmentation-using-the-color-thesholder-app.html
        
        % Convert RGB image to chosen color space
        I = rgb2hsv(RGB);

        % Define thresholds for channel 1 based on histogram settings
        channel1Min = 0.925;
        channel1Max = 0.022;

        % Define thresholds for channel 2 based on histogram settings
        channel2Min = 0.202;
        channel2Max = 0.888;

        % Define thresholds for channel 3 based on histogram settings
        channel3Min = 0.700;
        channel3Max = 1.000;
        
        % Create mask based on chosen histogram thresholds
        sliderBW = ( (I(:,:,1) >= channel1Min) | (I(:,:,1) <= channel1Max) ) & ...
            (I(:,:,2) >= channel2Min ) & (I(:,:,2) <= channel2Max) & ...
            (I(:,:,3) >= channel3Min ) & (I(:,:,3) <= channel3Max);
        BW = sliderBW;
        
        % Initialize output masked image based on input image.
        maskedRGBImage = RGB;
        
        % Set background pixels where BW is false to zero.
        maskedRGBImage(repmat(~BW,[1 1 3])) = 0;
                
        % Determine the connected areas and their centroid
        % https://www.mathworks.com/help/images/ref/bwconncomp.html is easier.
        
        CC = bwconncomp(sliderBW);
        
        s = regionprops(CC,'Centroid','Area');
        centroids = cat(1,s.Centroid);
        areas = cat(1,s.Area);
        [m,ind] = max(areas); % find the largest connected component 
        
        currentImageSize = m;
                 
        if CC.NumObjects == 0
            disp('no image detected');
        elseif currentImageSize < 1000
            disp('igore the object (too small)');
        else
            % put a star on the largest connected component. 
            % This is where you should aim your robot.
            if imageOutput == 1
                subplot(3,1,1), imshow(RGB)
                subplot(3,1,2), imshow(maskedRGBImage)
                subplot(3,1,3), imshow(double(sliderBW))
                hold on
                plot(centroids(ind,1),centroids(ind,2),'m*','markersize',32) 
                hold off
            end
            imageDetection = 1;
        end
        
        %%% motor control %%%
        
        if operationCompletion == 1
            
            disp('operation done');
            
        elseif pickupCompletion == 1
            
            % back to default position (-65deg, 65deg, 0deg)
            M2control = 785;
            M3control = 600;
            M4control = 530;
            armControl3D(device, M2control, M3control, M4control);
            readPotentiometer(device);
            
%             openEndeffector(device);
            
            operationCompletion = 1;
            
        elseif validControl == 1
            
            % Step3 : calculate the control value (potentiometer)
            [p2, p3] = getControlVariables(q2_deg, q3_deg);
            armControl2D(device, p2, p3);
            pause(3); 
            
            closeEndeffector(device);
            
            pickupCompletion = 1;
            
        elseif alighDirection == 1
            
            % Step2 : solve inverse kinematics for q2 and q3
            [q2, q3, q2_deg, q3_deg] = getJointVariables(centroidC); 
            validControl = 1;
            
            if q2_deg > 110 || q2_deg < -110
                disp('out of workspace: motor2');
                validControl = 0;
            end
            if q3_deg > 160 || q3_deg < 10
                disp('out of workspace: motor3');
                validControl = 0;
            end
            
        elseif imageDetection == 1
            
            % extract the cordinates of object centroid
            centroidR = centroids(ind,1)
            centroidC = centroids(ind,2)
                        
            % image size is 1080 x 1920 -> the center of image is (960, 540)
            centerOfImageR = 960;
            centerOfImageC = 540;

            % Bang-bang control precision parameter
            controlError = 20; % pixel

            % STEP1: aligh the arm to the object direction
            errorR = centerOfImageR - centroidR;
            
            if errorR > controlError
                alighDirection = 0;
            elseif errorR < -1*controlError
                alighDirection = 0;
            else
                alighDirection = 1;
                disp('alignment done');
                pause(3); 
            end
            
            if alighDirection == 0
                controlR = cast(abs(errorR)/10,'uint8');
                controlR2 = rem(controlR, 10);
                controlR1 = (controlR-controlR2)/10;
                if errorR > controlError
                    writeline(device,"g"+stringConversion(controlR1)+stringConversion(controlR2));
                    readline(device);
                    readline(device);
                    readline(device);
                elseif errorR < -1*controlError
                    writeline(device,"h"+stringConversion(controlR1)+stringConversion(controlR2));
                    readline(device);
                    readline(device);
                    readline(device);
                end
                pause(3); 
            end
            
        end
        
        if mode == 2
            continuous = 0;
        end
        
    end
    
end


if mode == 4
    readPotentiometer(device);
    % back to default position (-65deg, 65deg, 0deg)
    M2control = 785;
    M3control = 600;
    M4control = 530;
    armControl3D(device, M2control, M3control, M4control);
    readPotentiometer(device);
    openEndeffector(device);
end

if mode == 5
    % Identify configuration space
    r1 = 11;
    r2 = 20;
    z = -14.5;
    Result = zeros(20,3);
    
    for distance = 10:27
        
        cosA = (distance^2 + z^2 -r1^2 - r2^2)/(-2*r1*r2);
        A = acos(cosA);
        q2 = -(pi - A);
        q2_deg = q2/(2*pi)*360;

        cosB = distance/(distance^2 + z^2)^0.5;
        B = acos(cosB);
        cosC = (r1+r2*cos(-1*q2))/(distance^2 + z^2)^0.5;
        C = acos(cosC);
        
        if z < 0
            q3 = C-B;
        else
            q3 = C+B;            
        end
        q3_deg = q3/(2*pi)*360;
        
        Result(distance,1) = distance;
        Result(distance,2) = q2_deg;
        Result(distance,3) = q3_deg;
        
    end
    
    
end



function [b] = stringConversion(a)
    if a == 1
        b = '1';
    elseif a == 2
        b = '2';
    elseif a == 3
        b = '3';
    elseif a == 4
        b = '4';
    elseif a == 5
        b = '5';
    elseif a == 6
        b = '6';
    elseif a == 7
        b = '7';
    elseif a == 8
        b = '8';
    elseif a == 9
        b = '9';
    else
        b = '0';
    end
end


function [q2, q3, q2_deg, q3_deg] = getJointVariables(centroidC)
    
    distance = 31.4 - 0.0191*centroidC
    r1 = 11;
    r2 = 20;
    z = -14.5;
    
    cosA = (distance^2 + z^2 -r1^2 - r2^2)/(-2*r1*r2);
    A = acos(cosA);
    
    q2 = -(pi - A);
    q2_deg = q2/(2*pi)*360
    
    cosB = distance/(distance^2 + z^2)^0.5;
    B = acos(cosB);
    
    cosC = (r1+r2*cos(-1*q2))/(distance^2 + z^2)^0.5;
    C = acos(cosC);
    
    if z < 0
        q3 = C-B;
    else
        q3 = C+B;            
    end
    
    q3_deg = q3/(2*pi)*360
        
end


function [p2, p3] = getControlVariables(q2_deg, q3_deg)
    
%     motor 2 caliburation
%     0deg -> 520
%     3deg = 10

    p2 = int32(520 - 3.67 * q2_deg)

%     motor 3 calibration 
%     +90 -> 530
%     3deg = 10

    p3 = int32(850 - 3.55 * q3_deg)

end


function [] = armControl3D(device, p2, p3, p4)
       
    M2control = p2;
    M3control = p3;
    M4control = p4;
    
    M2control_3 = rem(M2control, 10);
    M2control_2 = rem((M2control-M2control_3),100)/10;
    M2control_1 = (M2control - M2control_2*10 -M2control_3) /100;
    
    M3control_3 = rem(M3control, 10);
    M3control_2 = rem((M3control-M3control_3),100)/10;
    M3control_1 = (M3control - M3control_2*10 - M3control_3) /100;

    M4control_3 = rem(M4control, 10);
    M4control_2 = rem((M4control-M4control_3),100)/10;
    M4control_1 = (M4control - M4control_2*10 - M4control_3) /100;       
            
    writeline(device,"m"+stringConversion(M3control_1)+stringConversion(M3control_2)+stringConversion(M3control_3));
    readline(device)
    readline(device)
    pause(3); 
        
    writeline(device,"l"+stringConversion(M2control_1)+stringConversion(M2control_2)+stringConversion(M2control_3));
    readline(device)
    readline(device)
    pause(3); 
    
    writeline(device,"n"+stringConversion(M4control_1)+stringConversion(M4control_2)+stringConversion(M4control_3));
    readline(device)
    readline(device)
    pause(3); 
end

function [] = armControl2D(device, p2, p3)
       
    % back to default position (0deg, 45deg, -45deg)
    M2control = p2;
    M3control = p3;
    
    M2control_3 = rem(M2control, 10);
    M2control_2 = rem((M2control-M2control_3),100)/10;
    M2control_1 = (M2control - M2control_2*10 -M2control_3) /100;
    
    M3control_3 = rem(M3control, 10);
    M3control_2 = rem((M3control-M3control_3),100)/10;
    M3control_1 = (M3control - M3control_2*10 - M3control_3) /100;

    writeline(device,"m"+stringConversion(M3control_1)+stringConversion(M3control_2)+stringConversion(M3control_3));
    readline(device)
    readline(device)
    pause(3); 
    
    writeline(device,"l"+stringConversion(M2control_1)+stringConversion(M2control_2)+stringConversion(M2control_3));
    readline(device)
    readline(device)
        
end

function [] = readPotentiometer(device)
    writeline(device,"r");
    readline(device)
    readline(device)
    readline(device)
    readline(device)
    readline(device)
end

function [] = openEndeffector(device)
    writeline(device,"j");
    readline(device)
end

function [] = closeEndeffector(device)
    writeline(device,"i");
    readline(device)
end



