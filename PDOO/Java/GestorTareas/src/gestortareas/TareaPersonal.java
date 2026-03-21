/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gestortareas;

/**
 *
 * @author Jaime Espín
 */
public class TareaPersonal extends Tarea{

    public TareaPersonal(String titulo, String descripcion, Prioridad prioridad) {
        super(titulo, descripcion, prioridad);
    }

    @Override
    public String mostrarDetalles() {
        return super.getTitulo()+" "+super.getDescripcion();
    }

    @Override
    public TipoTarea getCategoria() {
        return TipoTarea.PERSONAL;
    }
    
}
