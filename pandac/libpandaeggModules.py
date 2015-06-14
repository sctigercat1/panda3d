from extension_native_helpers import *
from panda3d.egg import *

####################################################################
#Dtool_funcToMethod(func, class)        
#del func
#####################################################################
    # For iterating over vertices
def getVertices(self):
        """Returns a Python list of the egg primitive's vertices."""
        result = []
        for i in range(self.getNumVertices()):
            result.append(self.getVertex(i))
        return result
Dtool_funcToMethod(getVertices, EggPrimitive)        
del getVertices

####################################################################
#Dtool_funcToMethod(func, class)        
#del func
#####################################################################
    # For iterating over children
def getChildren(self):
        """Returns a Python list of the egg node's children."""
        result = []
        child = self.getFirstChild()
        while (child != None):
            result.append(child)
            child = self.getNextChild()
        return result
    
Dtool_funcToMethod(getChildren, EggGroupNode)        
del getChildren

