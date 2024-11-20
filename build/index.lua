local imports = {
  require("scripts/test"),
  require("scripts/test2"),
}

State = {
  name = "Anon",
  val=0
}

function NextState()
  print("[LUA] Next State called")
  for key,value in pairs(imports) do
    if value.nextState ~= nil then
      value.nextState()
    end
  end
end
