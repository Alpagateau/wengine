return {
nextState = function()
  if(State["chap"] ~= 1) then return end
  if(State["intro"] == nil) then
    State["intro"] = 0
    loadImg("tie.tsi")
    say("Me voila\n ")
    say("La porte est devant moi.\n ")
    State["toque"] = 0
    while State["toque"] == 0 do
      ask({
          {"Relire l'adresse", 
            function()
              say("\n:0000FF:Relire l'adresse")
              say("92 rue des Vignoles")
            end},
          {"Toquer",
          function()
            say("\n:0000FF:Toquer")
            State["toque"] = 1
          end},
        })
    end
    loadImg("door.tsi")
    say(":6A6A6A:Toc. toc. toc.\n ") 
    say("Je vois une ombre")
    say("passer devant l'oeilleton")
    say("\n<dl>C'est pour quoi ?<dg>\n ")
    say("Une vielle dame ouvre la\n porte\n ")
    say("\"Bonjour madame !\"")
    say("\"Je viens vous parler de")
    say("J<é>sus christ\"")
    say("\"Notre sauveur a tous\"")
    say("\"Auriez vous un peu de\n temps a m'accorder?\"\n ")
    say("Elle m'observe d'un\n regard doux.\n ")
    say("<dl>Entre donc<dg>")
    say("<dl>Viens prendre un th<é><dg>")
    while State["inside"] ~= 1 do 
      ask({
          {"Accepter",
            function()
              State["inside"]=1
              say("\"Ce serai avec plasir\"")
            end
          },
          {"Refuser",
            function()
              say("\"Non merci\"")
              say("Elle ne bouge pas")
              say("Elle ne dit rien")
            end
          }
        })
    end
  end
end
}
