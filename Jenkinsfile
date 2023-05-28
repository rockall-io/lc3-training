pipeline {

    agent any

    stages {
        stage('build') {
            steps {
                sh "cmake -S . -B build"
                sh"cmake --build build --config Release --verbose --parallel 4"
            }
        }
        stage('test') {
            steps {
                dir("build") {
                    sh "lc3tests"
                }
            }
        }
    }

}