from PyPluginLib import PluginLib

def InitPlugin(plugin : PluginLib):
    print("Plugin Registered: " + plugin.GetName())
    pass

def PlayRound(plugin : PluginLib):
    print("Played Round: " + plugin.GetName())
    pass