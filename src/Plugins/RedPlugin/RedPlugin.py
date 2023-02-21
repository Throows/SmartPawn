import PyPluginLib

def InitPlugin(plugin):
    print("Plugin Registered: " + plugin.name)
    return 0

def PlayRound(plugin):
    print("Played Round: " + plugin.name)
    coords = plugin.GetMyFirstPawn()
    plugin.SetAction(coords, PyPluginLib.MoveType.UP)
    return 0