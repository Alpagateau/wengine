local imports = {
  require("scripts/test"),
  require("scripts/test2"),
}

State = {
  name = "Anon",
}

for key,value in pairs(imports) do
  if value.nextState ~= nil then
    value.nextState()
  end
end
