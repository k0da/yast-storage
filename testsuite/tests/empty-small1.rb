# encoding: utf-8

# testedfiles: helper1b.yh
module Yast

  class TestClient < Client

    def main
      Yast.include self, "setup-system.rb"

      setup_system("empty-small")

      Yast.include self, "helper1a.rb"

      Yast.import "ProductFeatures"

      ProductFeatures.SetBooleanFeature("partitioning", "try_separate_home", true)
      ProductFeatures.SetBooleanFeature("partitioning", "proposal_lvm", false)
      ProductFeatures.SetBooleanFeature("partitioning", "proposal_snapshots", true)
      ProductFeatures.SetStringFeature("partitioning", "root_base_size", "10 GB")

      def setup3()
      end

      Yast.include self, "helper1b.rb"

      nil
    end

  end

end

Yast::TestClient.new.main
