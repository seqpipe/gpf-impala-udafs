pipeline {
    agent {
        label 'dory'
    }
    options {
        disableConcurrentBuilds()
    }
    triggers {
        pollSCM('* * * * *')
        cron('H 2 * * *')
    }

    environment {
        WD="${env.WORKSPACE}"

        GPF_UDAF_IMAGE="gpf_udaf_image${env.BRANCH_NAME}_${env.BUILD_NUMBER}"
        GPF_UDAF_CONTAINER="gpf_kmpala_udaf_test${env.BRANCH_NAME}_${env.BUILD_NUMBER}"
    }
    stages {
        stage ('Start') {
            steps {
                slackSend (
                    color: '#FFFF00',
                    message: "STARTED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]' ${env.BUILD_URL}"
                )
            }
        }

        stage('Build UDAF devel image') {
            steps {
                sh '''
                    $WD/build_container.sh
                '''
            }
        }

        stage('Compile and run tests') {
            steps {
                sh '''
                    ${WD}/run_container.sh
                '''
            }
        }
    }
    post {
        success {
            slackSend (
                color: '#00FF00',
                message: "SUCCESSFUL: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]' ${env.BUILD_URL}"
            )
        }
        failure {
            slackSend (
                color: '#FF0000',
                message: "FAILED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]' ${env.BUILD_URL}"
            )
        }
    }
}
