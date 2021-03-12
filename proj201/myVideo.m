%% get file name and error rate
user_video_file = input('Enter the name of the video file: ' , 's');
videoFileReader = VideoReader(user_video_file);
error_rate = input('Enter the amount of error rate for the video file (between 0 and 1): ');
%% get size of a frame to initilaize empty matrix
frame = readFrame(videoFileReader);
[NumOfrows, NumOfcolumns, NumOfpages] = size(frame);
DecMatrix = uint8(zeros(NumOfrows, NumOfcolumns, NumOfpages));
%% initialize videoreader and videowriter
videoFileReader = VideoReader(user_video_file);
myVideoFile = VideoWriter('myVideo','MPEG-4');
myVideoFile.FrameRate = videoFileReader.FrameRate;
%% read & write each frame
open(myVideoFile);
while hasFrame(videoFileReader)
    videoFrame = readFrame(videoFileReader);
    m = 1;
    i = 1;
    while((m <= NumOfcolumns) || (i <= NumOfpages))    
       BinaryColumn = dec2bin(videoFrame(:,m,i), 8);
       for index = 1:1:NumOfrows
           for h = 1:1:8
               Random_Number = rand;
               if (Random_Number <  error_rate)
                   if (BinaryColumn(index, h) == '1')
                       BinaryColumn(index, h) = '0';
                   elseif (BinaryColumn(index, h) == '0')
                       BinaryColumn(index, h) = '1';
                   end
               end
           end          
       end
       DecColumn = uint8(bin2dec(BinaryColumn));
       DecMatrix(:,m,i) = uint8(DecColumn);
       m = m+1;
       if (m > NumOfcolumns)
           i = i+1;
           m = 1;
       end
       if (i > NumOfpages)
           m = NumOfcolumns + 1;
       end  
       
    end
    
    writeVideo(myVideoFile, DecMatrix);   
end
close(myVideoFile);
