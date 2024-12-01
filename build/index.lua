local imports = {
  require("scripts/chap1"),
  require("scripts/chap2")
}

State = {
  name = "Anon",
  fin = false,
  chap = 1
}

function NextState()
  if State["fin"]==true then return end
  for key,value in pairs(imports) do
    if value.nextState ~= nil then
      value.nextState()
    end
  end
end
