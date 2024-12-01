return {
  nextState = function()
    if State["chap"] ~= 2 then return end
    if State["kettle"] == nil then
      loadImg("kettle.tsi")
      State["kettle"] = 0
      clr()
      say("\nJe m'essuie les pieds\n sur le paillasson", 2)
      say("\nsallisant le texte qui\n y figure", 2)
      say("\n\'Abandon All Hope\'", 2)
      say("\'All Ye Who Enter\'", 1)
      say("\nJe sais pas ce que <cced>a\n veux dire", 3)
      say("\nJe la suis dans l'entr<é>e", 2)
      say("\nMes pas grinces sur le\n vieux parquet", 2)
      say(" Les murs verts se marient\n"..
          " tres bien avec les vases\n"..
          " et autres babioles qui\n"..
          " d<é>corent le couloir", 5)
      say("Au bout de ce couloir,\n"..
          " je vois la fenetre qui\n"..
          " donne sur une cour\n".." interieur", 5)
      say("\n<dl>Viens donc t'assoir\n dans la cuisine<dg>", 2)
      State["explored"] = 0
      State["in_kitchen"] = 0
      while State["in_kitchen"] == 0 do
        ask({
            {"Aller dans la cuisine", function() State["in_kitchen"]=1 end},
            {"Explorer", function()
              say("\n:0000EE:Explorer", 2)
              State["in_kitchen"]=0
              State["explored"] = State["epxlored"]+1
            end}
          })
        if State["in_kitchen"] == 0 then
          if State["explored"] == 1 then
            say("\nSur le mur, quelques\n"..
                " photos represente une\n"..
                " jeune femme, fusils a la main\n ,au cot<é>"..
                " d'un \n<é>l<é>phant mort", 5)
            say("\nUne autre montre un\n"..
                " groupe d'ecoterroriste\n"..
                " devant une <é>glise\n", 2)
            say("L'appartement n'est pas\n"..
                " bien grand en soit", 3)
            say("Mais la d<é>coration lui\n"..
                " lui done des airs ", 3)
          end
          if State["explored"] == 2 then
            say("Depuis l'entr<é>e, j'apper<cced>ois\n".." un crucifix", 2)
            say("La pauvre ne doit pas parler\n"..
                " latin", 3)
            say("\nAu lieu du INRI habituel,\n il est <é>crit INPI...", 3)
            say("\nPi<è>tre qualit<é>", 2)
            say("\nJe devrai la rejoindre maintenant", 2)
            State["in_kitchen"] = 1
          end
          State["explored"] = 1 + State["explored"]
        end
      end
    end


    say("Je m'assoie <à> table", 2)
    State["chap"] = 3
  end
}
