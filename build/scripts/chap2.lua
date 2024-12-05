return {
  nextState = function()
    if State["chap"] ~= 2 then return end
    if State["kettle"] == nil then
      loadImg("kettle.tsi")
      State["kettle"] = 0
      clr()
      say("\nJe m'essuie les pieds sur le paillasson", 2)
      say("\nsallisant le texte qui y figure", 2)
      say("\n\'Abandon All Hope\'", 2)
      say("\'All Ye Who Enter\'", 1)
      say("\nJe sais pas ce que <cced>a veux dire", 3)
      say("\nJe la suis dans l'entr<é>e", 2)
      say("\nMes pas grinces sur le vieux parquet", 2)
      say("Les murs verts se marient"..
          " tres bien avec les vases"..
          " et autres babioles qui"..
          " d<é>corent le couloir", 6)
      say("\nAu bout de ce couloir,"..
          " je vois la fenetre qui"..
          " donne sur une cour".." interieur", 6)
      say("\n<dl>Viens donc t'assoir dans la cuisine<dg>", 2)
      State["explored"] = 0
      State["in_kitchen"] = 0
      while State["in_kitchen"] == 0 do
        ask({
            {"Aller dans la cuisine", function() State["in_kitchen"]=1 end},
            {"Explorer", function()
              say("\n:0000EE:Explorer", 2)
              State["in_kitchen"]=0
              State["explored"] = State["explored"]+1
            end}
          })
        if State["in_kitchen"] == 0 then
          if State["explored"] == 1 then
            say("\nSur le mur, quelques"..
                " photos represente une"..
                " jeune femme, fusils a la main ,au cot<é>"..
                " d'un <é>l<é>phant mort", 6)
            say("\nUne autre montre un"..
                " groupe d'ecoterroriste"..
                " devant une <é>glise", 3)
            say("\nL'appartement n'est pas"..
                " bien grand en soit", 3)
            say("\nMais la d<é>coration lui"..
                " lui done des airs ", 3)
          end
          if State["explored"] == 2 then
            say("\nDepuis l'entr<é>e, j'apper<cced>ois un crucifix", 2)
            say("\nLa pauvre ne doit pas parler"..
                " latin", 3)
            say("\nAu lieu du INRI habituel, il est <é>crit INPI...", 3)
            say("\nPi<è>tre qualit<é>", 2)
            say("\nJe devrai la rejoindre maintenant", 2)
            State["in_kitchen"] = 1
          end
          State["explored"] = 1 + State["explored"]
        end
      end
    end


    say("\nJe m'assoie <à> table", 4)
    State["chap"] = 3
  end
}
