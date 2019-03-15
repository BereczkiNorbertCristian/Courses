clear all;

load('trackList.mat');
brake = zeros(1,5);
idx = zeros(1,5);

for i=1:length(trackList)
    M = length(trackList(i).objAttributes.dxVec);
    attrs = trackList(i).objAttributes;

    for j=1:M
        % EXTRACT
        dx = attrs.dxVec(j);
        dy = attrs.dyVec(j);
        vx = attrs.vxVec(j);
        vy = attrs.vyVec(j);
        wExist = attrs.wExistVec(j);
        wObst = trackList(i).objType.prob1Obstacle(j);
        wPed = trackList(i).objType.obstacle_Mobile_prob1Pedestrian(j);
        vEgo = trackList(i).vehAttributes.vEgo(j);
        
        % COMPUTE
        if (wExist > .95 && wPed > .8 && wObst > .8)
            if (vy > (vEgo + vx) && abs(dy) < 1)
                if (vEgo > 14 && dx < 15)
                    brake(i) = trackList(i).cycles(j);
                    idx(i) = j;
                    fprintf("The guy braked at idx=%d with speed %.3f and dx=%.3f\n",j,vEgo,dx);
                    break;   
                end
                if (vEgo < 14 && vEgo > 9.7 && dx < 9)
                    brake(i) = trackList(i).cycles(j);
                    idx(i) = j;
                    fprintf("The guy braked at idx=%d with speed %.3f and dx=%.3f\n",j,vEgo,dx);
                    break;
                end
                if (vEgo < 9.7 && dx < 6)
                    brake(i) = trackList(i).cycles(j);
                    idx(i) = j;
                    fprintf("The guy braked at idx=%d with speed %.3f and dx=%.3f\n",j,vEgo,dx);
                    break;
                end
            end
        end
    end
end
brake
idx