return {
nextState = function()
  if(State["chap"] ~= 1) then return end
  if(State["intro"] == nil) then
    State["intro"] = 0
    loadImg("tie.tsi")
    say("Me voila\n ", 2)
    say("La porte est devant moi.\n ", 2)
    State["toque"] = 0
    while State["toque"] == 0 and State["fin"] == false do
      a = ask({
          {"Relire l'adresse", 
            function()
              say("\n:0000FF:Relire l'adresse", 2)
              say("92 rue des Vignoles", 2)
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
    say(":6A6A6A:Toc. toc. toc.\n ",2)
    say("Je vois une ombre",2)
    say("passer devant l'oeilleton", 2)
    say("\n<dl>C'est pour quoi ?<dg>\n ", 2)
    say("Une vielle dame ouvre la\n porte\n ", 2)
    say("\"Bonjour madame !\"", 2)
    say("\"Je viens vous parler de", 2)
    say("J<é>sus christ\"", 2)
    say("\"Notre sauveur a tous\"", 2)
    say("\"Auriez vous un peu de\n temps a m'accorder?\"\n ", 2)
    say("Elle m'observe d'un\n regard doux.\n ", 2)
    say("<dl>Entre donc<dg>", 2)
    say("<dl>Viens prendre un th<é><dg>", 2)
    while State["inside"] ~= 1 and State["fin"] == false do
      a=ask({
          {"Accepter",
            function()
              State["inside"]=1
              say("\"Ce serai avec plasir\"", 2)
            end
          },
          {"Refuser",
            function()
              say("\"Non merci\"\n ", 2)
              say("Elle ne bouge pas", 3)
              say("Elle ne dit rien", 3)
            end
          }
        })
      if a==false then
        State["fin"] = true;
      end
    end
    say("<dl>L'eau est d<é>ja chaude<dg>\n ", 2)
    State["chap"]=2
  end
end
}
