# Tooling for jupyter notebook/lab

# Jupyter notebook tooling
# TODO: See
# https://stackoverflow.com/questions/73218304/how-to-clear-jupyter-notebooks-output-and-metadata-when-using-git-commit
# and apply in Git instead as that seems to be a much better alternative
# or alternatively do it with jq for SPEEEEED according to:
#   https://stackoverflow.com/questions/28908319/how-to-clear-jupyter-notebooks-output-in-all-cells-from-the-linux-terminal/58004619#58004619
#   https://timstaley.co.uk/posts/making-git-and-jupyter-notebooks-play-nice/
# another alternative:
#   https://nbdev.fast.ai/tutorials/git_friendly_jupyter.html
add_custom_target(git-prepare-jupyter
    COMMAND find 20* -type f -name '*.ipynb'
        | grep -v ipynb_checkpoint
        | xargs -i{} jupyter nbconvert --ClearOutputPreprocessor.enabled=True --ClearMetadataPreprocessor.enabled=True --inplace {}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
