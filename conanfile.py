import conans


class BoilerplateConan(conans.ConanFile):
    generators = ["pkg_config", "cmake"]
    settings = "os", "compiler", "build_type", "arch"
    requires = ["boost/1.81.0", "icu/72.1"]
    default_options = {"icu:data_packaging": "static"}

    def build(self):
        meson = conans.Meson(self)
        meson.configure()
        meson.build()
