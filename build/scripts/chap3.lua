return {
  nextState = function()
    if State["chap"] ~= 3 then return end
    loadImg("frame.tsi")
    say("<dl>Donne-moi quelques instants<dg>", 3)
    say("<dl>Je vais chercher des gateaux<dg>", 3)
    say("\nElle farfouille dans ses placards", 2)
    say(" qui semblent bien plus profonds\n qu'ils en ont l'air", 4)
    say("Sur la table devant moi,\n se tient un verre Duralex", 3)
    ask({
      {"Regarder mon age",
        function()
          say("\nJe regarde mon age au fond de celui ci", 3)
          say("\nJ'ai 66 ans", 4)
        end},
      {"Attendre patiemment", function() end}
    })
    say("\n<dl>Voil<à> les g<â>teaux<dg>", 3)
    say("\n<dl>Plus que les infusions et tu es a moi<dg>", 3)
    say("\n\"Superbe, pas de probl<è>mes\"", 3)
    say("\nL'expression n'est pas plut<ô>t \'Je suis a toi\'?", 2)
    say("La pauvre n'est pas abile de ses mots", 3)

    say("Elle pose sur la table...", 3)
    say("Une boite de couture ?", 3)
    say("Je dirige mon regard penaud vers la grand m<è>re", 2)
    say("Elle n'as pas l'ai de reagir <à> son erreur", 3)
    ask({
      {"Ouvrir la boite", function() State["box"] = 1 end},
      {"Ne rien faire", function() State["box"] = 2 end}
    })

    if State["box"] == 1 then
      say("\nPar automatisme, je jette un oeuil dans la boite", 4)
      say("NOM D'UNE PIPE EN BOIS", 3)
      say("Des biscuits britanniques !?", 3)
      say("Dans ce pays", 2)
      say("En cette saison", 2)
      say("Localis<é> enti<è>rement dans une boite\n de n<é>cessaire de couture ?", 4)
      say("Voila qui est des plus <é>tranges", 5)
      say("D<é>cid<é>ment, le troisi<è>me age me suprendra toujours.", 3)
    end
    if State["box"] == 2 then
      say("\nElle a l'air confiante de son geste", 3)
      say("Je lui accorde le b<é>n<é>fice du doute", 3)
    end
    say("<dl>Voici le th<é><dg>", 2)
    say("<dl>Ne t'<é>bouillante pas<dg>", 3)
    say("\"Merci beaucoup\"", 3)

    say("Elle verse le th<é>", 1)
    say("DE LA MAIN GAUCHE ?!",3)
    say("Voil<à> qui est irrespectueux !", 3)
    say("Je prie qu'elle ne soit pas"..
       " r<é>ellement gauch<è>re", 3)
    say("ce serait disgracieux")
    say("...", 2)
    say("Bon, passons", 2)
    say("En tant que bon ch<é>tien,"..
        " je me dois de lui pardonner", 3)

    State["chap"] = 1
  end
}
