pipeline {

    agent any

    stages {
        stage('build') {
            steps {
                sh {
                    "cmake -S . -B build"
                    "cmake --build build --config Release --verbose --parallel 4"
                }
            }
        }
        stage('test') {
            steps {
                sh {
                    "build/lc3tests"
                }
            }
        }
    }

}