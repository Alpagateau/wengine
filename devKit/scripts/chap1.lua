return {
nextState = function()
  if(State["chap"] ~= 1) then return end
  if(State["intro"] == nil) then
    State["intro"] = 0
    loadImg("tie.tsi")
    say("Me voila", 2)
    say("\nLa porte est devant moi.", 2)
    State["toque"] = 0
    while State["toque"] == 0 and State["fin"] == false do
      local a = ask({
          {"Relire l'adresse",
            function()
              say("\n:0000FF:Relire l'adresse", 2)
              say("\n92 rue des Vignoles", 2)
            end},
          {"Toquer",
          function()
            say("\n:0000FF:Toquer", 2)
            State["toque"] = 1
          end},
        })
      if a == false then
        State["fin"] = true;
      end
    end
    loadImg("door.tsi")
    say(":6A6A6A:Toc. toc. toc.",2)
    say("\nJe vois une ombre passer",2)
    say("devant l'oeilleton", 2)
    say("\n<dl>C'est pour quoi ?<dg>", 2)
    say("\nUne vielle dame ouvre la\n porte", 2)
    say("\n\"Bonjour madame !\"", 2)
    say("\"Je viens vous parler de", 2)
    say("J<é>sus christ\"", 2)
    say("\"Notre sauveur <à> tous\"", 2)
    say("\"Auriez vous un peu de\n temps <à> m'accorder?\"\n ", 2)
    say("Elle m'observe d'un\n regard doux.\n ", 2)
    say("<dl>Entre donc<dg>", 2)
    say("<dl>Viens prendre un th<é><dg>", 2)
    while State["inside"] ~= 1 and State["fin"] == false do
      local a=ask({
          {"Accepter",
            function()
              State["inside"]=1
              say("\"Ce serait avec plasir\"", 2)
            end
          },
          {"Refuser",
            function()
              if State["refuser"] == nil then
                State["refuser"] = 2
              else
                State["refuser"] = State["refuser"]+1
              end
              say("\"Non merci\"\n ", 2)
              print("[LUA] : "..State["refuser"])
              if State["refuser"] > 4 then
                say("C'est la fin, le tous dernier matin", 1)
                State["fin"] = true
              else
                say("Elle ne bouge pas", State["refuser"])
                say("Elle ne dit rien", State["refuser"])
              end
            end
          }
        })
      if a==false then
        State["fin"] = true;
      end
    end
    if State["fin"] then return end
    say("<dl>L'eau est d<é>ja chaude<dg>\n ", 2)
    State["chap"]=2
  end
end
}
