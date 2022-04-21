@Library('xmos_jenkins_shared_library@v0.18.0') _

// Wait here until specified artifacts appear
def artifactUrls = getGithubArtifactUrls([
    "xcore_sdk_bare-metal_example_apps"
    // "xcore_sdk_freertos_example_apps",
    // "xcore_sdk_freertos_usb_example_apps",
    // "xcore_sdk_host_apps",
    // "xcore_sdk_reference_apps",
    // "xcore_sdk_rtos_tests"
])

getApproval()

pipeline {
    agent {
        label 'sdk'
    }
    parameters {
        string(
            name: 'TOOLS_VERSION',
            defaultValue: '15.1.4',
            description: 'The XTC tools version'
        )
    }    
    environment {
        DIST_PATH = "dist"
        VENV_PATH = "./jenkins_venv"   // NOTE: Needs to be prepended with ./
        CONDA_PATH = "miniconda3"
        CONDA_EXE = "${CONDA_PATH}/bin/conda"
    }        
    options {
        skipDefaultCheckout()
    }    
    stages {
        stage('Download artifacts') {
            steps {
                dir("${DIST_PATH}") {
                    downloadExtractZips(artifactUrls)
                    // List extracted files for log
                    sh "ls -la"
                }
            }
        }
        stage('Create virtual environment') {
            steps {
                dir("${DIST_PATH}") {
                    // Create the venv
                    sh "wget https://repo.anaconda.com/miniconda/Miniconda3-py38_4.11.0-Linux-x86_64.sh -O conda_install.sh"
                    sh "bash conda_install.sh -b -p ${CONDA_PATH}"
                    sh "rm -rf conda_install.sh"
                    sh "${CONDA_EXE} create --prefix ${VENV_PATH} python=3.8"
                }
                dir("${DIST_PATH}") {
                    // Install dependencies
                    sh "${CONDA_EXE} run -p ${VENV_PATH} pip install git+https://github0.xmos.com/xmos-int/xtagctl.git"
                    // sh '''#!/usr/bin/env bash
                    // source ${CONDA_PATH}/etc/profile.d/conda.sh
                    // conda activate ./${VENV_PATH}
                    // pip install git+https://github0.xmos.com/xmos-int/xtagctl.git
                    // conda deactivate
                    // '''
                    // sh '''#!/usr/bin/env bash
                    // sh "source ${CONDA_PATH}/etc/profile.d/conda.sh"
                    // sh "${CONDA_PATH}/bin/conda activate ./${VENV_PATH}"
                    // sh "pip install git+https://github0.xmos.com/xmos-int/xtagctl.git"
                    // sh "${CONDA_PATH}/bin/conda deactivate"
                }
            }
        }
        stage('Cleanup xtagctl') {
            steps {
                dir("${DIST_PATH}") {
                    withTools(params.TOOLS_VERSION) {
                        // Cleanup any xtagctl cruft from previous failed runs
                        sh "${CONDA_EXE} run -p ${VENV_PATH} xtagctl status"
                        sh "${CONDA_EXE} run -p ${VENV_PATH} xtagctl reset_all XCORE-AI-EXPLORER"
                        // sh '''#!/usr/bin/env bash
                        // source ${CONDA_PATH}/etc/profile.d/conda.sh
                        // conda activate ./${VENV_PATH}
                        // xtagctl status
                        // xtagctl reset_all XCORE-AI-EXPLORER
                        // conda deactivate
                        // '''
                        // sh "source ${CONDA_PATH}/etc/profile.d/conda.sh"
                        // sh "${CONDA_PATH}/bin/conda init bash"
                        // sh "${CONDA_PATH}/bin/conda activate ./${VENV_PATH}"
                        // sh "xtagctl status"
                        // sh "xtagctl reset_all XCORE-AI-EXPLORER"
                        // sh "${CONDA_PATH}/bin/conda deactivate"
                    }
                    sh "rm -f ~/.xtag/status.lock ~/.xtag/acquired"
                }
            }
        }
        stage('Run bare-metal examples') {
            steps {
                dir("${DIST_PATH}") {
                    withTools(params.TOOLS_VERSION) {
                        sh "xrun --xscope example_bare_metal_vww.xe 2>&1 | tee example_bare_metal_vww.log"
                    }
                }
            }
        }
    }
    post {
        cleanup {
            cleanWs()
        }
    }
}