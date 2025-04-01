return {
nextState = function()
  if(State["chap"] ~= 1) then return end
  if(State["intro"] == nil) then
    State["intro"] = 0
    loadImg("tie.tsi")
    say("Me voila", 2)
    say("La porte est devant moi.", 2)
    State["toque"] = 0
    while State["toque"] == 0 and State["fin"] == false do
      local a = ask({
          {"Relire l'adresse",
            function()
              say(":0000FF:Relire l'adresse", 2)
              say("92 rue des Vignoles", 2)
            end},
          {"Toquer",
          function()
            say(":0000FF:Toquer", 2)
            State["toque"] = 1
          end},
        })
      if a == false then
        State["fin"] = true;
      end
    end
    loadImg("door.tsi")
    say(":6A6A6A:Toc. toc. toc.",2)
    say("Je vois une ombre passer a travers le judas", 3)
    say("\n<dl>C'est pour quoi ?<dg>", 2)
    say("\nUne vielle dame ouvre la porte", 2)
    say("\n\"Bonjour madame !\"", 2)
    say("\n\"Je viens vous parler de J<é>sus Christ\" !", 2)
    say("\"Notre sauveur <à> tous\"", 2)
    say("\"Auriez vous un peu de temps <à> m'accorder?\"", 2)
    say("\nElle m'observe d'un regard doux.", 2)
    say("\n<dl>Entre donc<dg>", 2)
    say("<dl>Viens prendre un th<é><dg>\n", 2)
    while State["inside"] ~= 1 and State["fin"] == false do
      local a=ask({
          {"Accepter",
            function()
              State["inside"]=1
              say("\n\"Ce serait avec plasir\"", 2)
            end
          },
          {"Refuser",
            function()
              if State["refuser"] == nil then
                State["refuser"] = 2
              else
                State["refuser"] = State["refuser"]+1
              end
              say("\"Non merci\"", 2)
              print("[LUA] : "..State["refuser"])
              if State["refuser"] > 4 then
                say("C'est la fin, le tous dernier matin", 1)
                State["fin"] = true
              else
                say("\nElle ne bouge pas", State["refuser"])
                say("\nElle ne dit rien", State["refuser"])
              end
            end
          }
        })
      if a==false then
        State["fin"] = true;
      end
    end
    if State["fin"] then return end
    say("<dl>L'eau est d<é>ja chaude<dg>", 2)
    State["chap"]=2
  end
end
}
