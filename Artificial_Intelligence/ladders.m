function [solutionFound] = ladders(start, goal)
%% Ladders!
% Author: Leonardo Freiherr von Lerchenfeld
% Date: 16.12.2017
 
%% Load wordlist
filename = 'wordList.txt';
delimiter = '';
formatSpec = '%s%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN, 'ReturnOnError', false);
fclose(fileID);
wordlist = dataArray{:, 1};
clearvars filename delimiter formatSpec fileID dataArray ans;

%% Initialization
len = length(wordlist);
alreadyused = cell(len,1);
alreadyused{1} = start;
iused = 2;
nextnode = cell(10000,1);
nextpath = cell(10000,30);
nextnode{1} = char(start);
nextpath{1,1} = start;
step = zeros(10000,1);
step(1) = acontainsb(start,goal);
lvl = 2; %Level how deep we are in the tree
if(stringtanga(start,goal)==1)
    solutionFound = 1;
else
    solutionFound = 0;
end
% Modify Wordlist
newwords = cell(20000,30);
inextword = ones(30,1);
for l=1:len
    nocc=cc(wordlist{l});
    newwords{inextword(nocc),nocc}=wordlist{l};
    inextword(nocc) = inextword(nocc)+1;
end

%% Search
while(solutionFound<1)
    [solutionFound,nextnode,nextpath,alreadyused,iused] = search(goal,nextnode,nextpath,alreadyused,iused,newwords,lvl,step);
    lvl = lvl+1;
    if(lvl==50)
        solutionFound=50;
    end
end

if(lvl==50)
    solutionFound=0;
else
print(wordlist,nextpath,solutionFound);
end

%% Function declarations
    function [nchars] = cc(x) %cc = count char
        nchars = sum((x >= 'a' & x <= 'z')); %| (x >= 'A' & x <= 'Z'));
    end

    function [new] = isused(word,alreadyused)
        new=1;
        for i=1:length(alreadyused)
            if(alreadyused{i}>0)
                if(stringtanga(word,alreadyused{i})==1)
                    new = 0;
                end
            else
                break%i=length(alreadyused);
            end
        end
    end

    function [samesame] = stringtanga(worda,wordb)
        samesame=0;
        lenc=length(wordb);
        if(lenc==length(worda))
            for i=1:lenc
                if(worda(i)==wordb(i))
                    samesame=1;
                else
                    samesame=0;
                    break
                end
            end  
        end
    end
        
    function [steps] = acontainsb(a,b)
        steps=0;
        for i=97:122 %ASCII Values of a=97 & z=122
            x1=length(find(a==char(i)));
            x2=length(find(b==char(i)));
            steps = steps + abs(x1-x2);
        end
    end

    function[solutionFound,nextnode,nextpath,aused,iused] = search(goal,xnode, xpath, aused,iused,wordlist,lvl,steps)
        % Initialization
        solutionFound=0;
        nextnode = cell(10000,1);
        nextpath = cell(10000,30);
        inext = 1;
        flag = 0;
        % Iterate over all possible candidates
        for j=1:length(xnode)
            if(xnode{j}>0)
                ncc = cc(xnode{j});
                for switchv=1:2
                    if(switchv==1)
                        ncc=ncc-switchv; %1 letter less
                    else
                        ncc=ncc+switchv; %1 letter more
                    end
                    for k=1:20000
                        if(wordlist{k,ncc}>0)%as long as there are words
                            if(acontainsb(wordlist{k,ncc},goal)<=steps(j)+1)
                               
                                if(acontainsb(wordlist{k,ncc},xnode{j})<2)
                                    % Avoid infinite loop by using every word
                                    % only once
                                    if(isused(wordlist{k,ncc},aused)==1)
                                        aused{iused}=wordlist{k,ncc};
                                        iused=iused+1;
                                        nextnode{inext}=wordlist{k,ncc};
                                        steps(inext)=acontainsb(wordlist{k,ncc},goal);
                                        for ii=1:30 % copy path
                                            if(xpath{j,ii}>0)
                                                nextpath{inext,ii}=xpath{j,ii};
                                            else
                                                break%ii=30;
                                            end
                                        end
                                        nextpath{inext,lvl}=wordlist{k,ncc};
                                        % GOAL
                                        if(stringtanga(goal,wordlist{k,ncc})==1)
                                            solutionFound=inext;
                                            flag=1;
                                            break
                                        else
                                            solutionFound=0;
                                        end
                                        inext=inext+1;
                                    end
                                end
                             
                            end     
                        else
                            break
                        end
                   end
                   if(flag==1)
                            break
                   end

                end

                if(flag==1)
                    break
                end
            else
                break%j=length(nextnode);
            end
        end
    end

    function print(wordlist,nextpath,solutionFound)
        fid = fopen( 'output.txt', 'wt' );
        for run=1:30 %insert print function here
            if(nextpath{solutionFound,run}>0)
                printme=nextpath{solutionFound,run};
                fprintf( fid, '%s\n', printme);
            else
                break
            end
        end
        
        fclose(fid);
    end

end
