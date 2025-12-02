{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };
  outputs = { self, nixpkgs, flake-utils }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};

      version = "0.1.0";

      nativeBuildInputs = with pkgs; [
        makeWrapper
        pkg-config
      ];

      buildInputs = [
        pkgs.python3
        pkgs.ruff
      ];
    in
      {
        devShells.${system}.default = pkgs.mkShell {
          inherit buildInputs nativeBuildInputs;

          CFLAGS="-Wall -Wextra -pedantic -std=c99 -ftrapv -Wconversion -Wsign-conversion -Wfloat-conversion -fsanitize=undefined -Wcast-qual -g -O0 -Wfatal-errors -Wno-cpp -fsanitize=signed-integer-overflow";
          LDFLAGS="-fsanitize=address -g -lm";
        };
      };
}
