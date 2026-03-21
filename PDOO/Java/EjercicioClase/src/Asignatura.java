/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
import java.util.ArrayList;

public class Asignatura {
    private int codigo;
    private String nombre;
    private Profesor profe;
    /*private int num_alumnos;
    private Alumno[] alumnos = new Alumno[num_alumnos];*/
    private ArrayList Alumnos;

    public Asignatura(int codigo, String nombre, Profesor profe/*, int num_alumnos*/) {
        this.codigo = codigo;
        this.nombre = nombre;
        this.profe = profe;
        /*this.num_alumnos = num_alumnos;*/
    }
    
    public Profesor getProfe() {
        return profe;
    }

    public ArrayList getAlumnos() {
        return Alumnos.clone();
    }
    
}
