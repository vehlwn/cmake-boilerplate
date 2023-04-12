from conan import ConanFile
from conan.tools.gnu import PkgConfigDeps
from conan.tools.meson import MesonToolchain, Meson


class BoilerplateConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    default_options = {"icu/*:data_packaging": "static"}

    def requirements(self):
        self.requires("boost/1.81.0")
        self.requires("icu/72.1")

    def generate(self):
        tc = MesonToolchain(self)
        tc.project_options["use_conan"] = "true"
        tc.generate()
        pc = PkgConfigDeps(self)
        pc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()
