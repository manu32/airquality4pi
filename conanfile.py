
import platform
from conans import ConanFile, CMake, tools


class ConanRecipe(ConanFile):

    name = "airquality4pi"
    version = "1.0.0-testing"
    description = ""
    author = "manu32"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    
    def build_requirements(self):
        self.build_requires("gtest/1.8.1@bincrafters/stable")
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()
